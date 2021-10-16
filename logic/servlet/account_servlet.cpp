#include "account_servlet.h"

#include <boost/exception/all.hpp>

#include "log/glog.h"
#include "net/https_request.h"

#include "logic/account_manager.h"
#include "logic/database/database.pb.h"
#include "logic/player_session.h"
#include "logic/player_session_manager.h"
#include "logic/protocol/protocol_error.h"
#include "logic/protocol/protocol_id.pb.h"
#include "logic/protocol/protocol_account.pb.h"
#include "logic/redis_key.h"
#include "logic/role.h"
#include "logic/server_config.h"
#include "logic/server_resource.h"
#include "logic/util.h"


enum {
    PT_TT = 1,
    PT_WX = 2,
};

static const std::string NAME_PREFIX = "用户";
static const std::string AVATAR_PREFIX = "https://eayew.com/resource/avatar/avatarurl_";
static const std::string AVATAR_SUFFIX = ".jpg";


bool AccountServlet::doRequest(Session::ptr session, uint16_t id, const std::string& buf) {
    auto ps = std::dynamic_pointer_cast<PlayerSession>(session);
    switch (id) {
        case Protocol::MsgId::C2S_ACCOUNT_LOGIN:
            return doLogin(ps, buf);

        case Protocol::MsgId::C2S_ACCOUNT_CREATE:
            return doCreate(ps, buf);

        case Protocol::MsgId::C2S_ACCOUNT_LOAD:
            return doLoad(ps, buf);

        case Protocol::MsgId::C2S_ACCOUNT_ASK_OPENID:
            return doAskOpenid(ps, buf);

        case Protocol::MsgId::C2S_ACCOUNT_UPDATE:
            return doUpdate(ps, buf);
    }

    return true;
}


bool AccountServlet::doLogin(std::shared_ptr<PlayerSession> ps, const std::string& buf) {
    LOG(INFO) << "AccountServlet doLogin";
    Protocol::C2S_AccountLogin reqMsg;
    if (!reqMsg.ParseFromString(buf)) {
        LOG(ERROR) << "ParseFromString fail, buf: " << buf;
        return false;
    }

    Protocol::S2C_AccountLogin resMsg;
    ServerResource::ptr res = ServerResource::get();

    //LOG(ERROR) << "---game id " << reqMsg.game_id() << "\topenid " << reqMsg.openid();
    long long roleId = AccountManager::roleId(reqMsg.game_id(), reqMsg.openid());
    //LOG(ERROR) << "---roleId: " << roleId;
    if (roleId <= 0) {
        resMsg.set_ret(ACCOUNT_NOT_EXIST);
        ps->send(Protocol::MsgId::S2C_ACCOUNT_LOGIN, resMsg);
        return true;
    }

    resMsg.set_role_id(roleId);
    ps->send(Protocol::MsgId::S2C_ACCOUNT_LOGIN, resMsg);

    return true;
}

bool AccountServlet::doCreate(std::shared_ptr<PlayerSession> ps, const std::string& buf) {
    LOG(INFO) << "AccountServlet doCreate";
    Protocol::C2S_AccountCreate reqMsg;
    if (!reqMsg.ParseFromString(buf)) {
        LOG(ERROR) << "ParseFromString fail, buf: " << buf;
        return false;
    }

    Protocol::S2C_AccountLoad resMsg;
    ServerResource::ptr res = ServerResource::get();
    auto role = Role::create();
    role->gameId(reqMsg.game_id());
    role->openid(reqMsg.openid());
    role->name(NAME_PREFIX + std::to_string(role->roleId()));
    int index = randInt(0, res->serverConfig()->avatarNum());
    role->avatarurl(AVATAR_PREFIX + std::to_string(index) + AVATAR_SUFFIX);
    role->flushToCache();

    // for doLoad
    ps->role(role);
    AccountManager::roleId(reqMsg.game_id(), reqMsg.openid(), role->roleId());

    resMsg.set_role_id(role->roleId());
    ps->send(Protocol::MsgId::S2C_ACCOUNT_LOAD, resMsg);

    return true;
}

bool AccountServlet::doLoad(std::shared_ptr<PlayerSession> ps, const std::string& buf) {
    LOG(INFO) << "AccountServlet doLoad";
    Protocol::C2S_AccountLoad reqMsg;
    if (!reqMsg.ParseFromString(buf)) {
        LOG(ERROR) << "ParseFromString fail, buf: " << buf;
        return false;
    }

    Protocol::S2C_AccountLoad resMsg;
    auto res = ServerResource::get();
    if (!ps->role()) {
        auto ps2 = res->psMgr()->getPlayer(reqMsg.game_id(), reqMsg.role_id());
        if (ps2) {
            ps->role(ps2->role());
        }
    }
    auto role = ps->role();
    if (!role) {
        ps->send(Protocol::MsgId::S2C_ACCOUNT_LOAD, resMsg);
        return true;
    }

    ServerResource::get()->psMgr()->playerOnline(ps);

    ps->send(Protocol::MsgId::S2C_ACCOUNT_LOAD, resMsg);

    return true;
}

static std::pair<bool, std::string> handleToutiaoAskOpenid(const std::string& appid, const std::string& secret, const std::string& code, const std::string& anonymous_code) {
    try {
        std::string host("developer.toutiao.com");
        std::string path("/api/apps/jscode2session");
        std::map<std::string, std::string> params;
        params["appid"] = appid;
        params["secret"] = secret;
        params["code"] = code;
        params["anonymous_code"] = anonymous_code;

        HttpsRequest hr;
        if (!hr.request(host, path, params)) {
            LOG(ERROR) << "handleToutiaoAskOpenid failed, appid: " << appid << "\tcode: " << code
                        << "\terror: " << boost::current_exception_diagnostic_information();
            return std::make_pair(false, "");
        }
        auto& root = hr.rspRoot();
        if (root.find("error") == root.not_found()) {
            return std::make_pair(false, "");
        }
        auto ec = root.get<int>("error");
        if (ec != 0) {
            auto errcode = root.get<int>("errcode");
            auto errmsg = root.get<std::string>("errmsg");
            auto message = root.get<std::string>("message");
            LOG(ERROR)<< "code2Session failed, errcode: " << errcode << "\terrmsg: " << errmsg << "\tmessage: " << message;
            return std::make_pair(false, "");
        }
        if (root.find("openid") != root.not_found()) {
            auto openid = root.get<std::string>("openid");
            if (!openid.empty()) {
                return std::make_pair(true, openid);
            }
        }
        if (root.find("anonymous_openid") != root.not_found()) {
            auto anonymous_openid = root.get<std::string>("anonymous_openid");
            if (!anonymous_openid.empty()) {
                return std::make_pair(true, anonymous_openid);
            }
        }
    } catch(...) {
        LOG(ERROR) << "handleToutiaoAskOpenid failed, appid: " << appid << "\tcode: " << code
                    << "error: " << boost::current_exception_diagnostic_information();
        return std::make_pair(false, "");
    }
    return std::make_pair(false, "");
}

bool AccountServlet::doAskOpenid(std::shared_ptr<PlayerSession> ps, const std::string& buf) {
    LOG(INFO) << "AccountServlet doAskOpenid";
    Protocol::C2S_AccountAskOpenid reqMsg;
    if (!reqMsg.ParseFromString(buf)) {
        LOG(ERROR) << "ParseFromString fail, buf: " << buf;
        return false;
    }

    std::string strGame;
    ServerResource::get()->rcPool()->hget(strGame, RedisKey::Game(), reqMsg.game_id());

    Database::Game game;
    Protocol::S2C_AccountAskOpenid resMsg;
    if (strGame.empty() || !game.ParseFromString(strGame)) {
        LOG(ERROR) << "game parse fail, strGame: " << strGame;
        resMsg.set_openid(std::to_string(getCurrentSecond()));
        ps->send(Protocol::MsgId::S2C_ACCOUNT_ASK_OPENID, resMsg);
        return true;
    }

    switch (game.platform()) {
        case PT_TT:     // toutiao
            auto ret = handleToutiaoAskOpenid(game.appid(), game.secret(), reqMsg.code(), reqMsg.anonymous_code());
            if (!ret.first) {
                resMsg.set_openid(std::to_string(getCurrentSecond()));
                break;
            }
            resMsg.set_openid(ret.second);
            break;
    }

    ps->send(Protocol::MsgId::S2C_ACCOUNT_ASK_OPENID, resMsg);

    return true;
}

bool AccountServlet::doUpdate(std::shared_ptr<PlayerSession> ps, const std::string& buf) {
    LOG(INFO) << "AccountServlet doUpdate";
    Protocol::C2S_AccountUpdate reqMsg;
    if (!reqMsg.ParseFromString(buf)) {
        LOG(ERROR) << "ParseFromString fail, buf: " << buf;
        return false;
    }

    Protocol::S2C_AccountUpdate resMsg;
    Role::ptr role = ps->role();
    if (!role) {
        return true;
    }

    role->name(reqMsg.name());
    role->avatarurl(reqMsg.avatarurl());
    role->country(reqMsg.country());
    role->city(reqMsg.city());
    role->flushToCache();

    ps->send(Protocol::MsgId::S2C_ACCOUNT_UPDATE, resMsg);
    return true;
}
