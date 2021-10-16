#include "rank_servlet.h"

#include "log/glog.h"
#include "redis/redis.h"

#include "logic/account_manager.h"
#include "logic/protocol/protocol_id.pb.h"
#include "logic/protocol/protocol_rank.pb.h"
#include "logic/marquee_manager.h"
#include "logic/player_session.h"
#include "logic/player_session_manager.h"
#include "logic/redis_key.h"
#include "logic/role.h"
#include "logic/server_config.h"
#include "logic/server_resource.h"
#include "logic/timer_field.h"


bool RankServlet::doRequest(Session::ptr session, uint16_t id, const std::string& buf) {
    auto ps = std::dynamic_pointer_cast<PlayerSession>(session);
    switch (id) {
        case Protocol::MsgId::C2S_RANK_LOAD:
            return doLoad(ps, buf);
        case Protocol::MsgId::C2S_RANK_UPDATE:
            return doUpdate(ps, buf);
    }
    return true;
}

bool RankServlet::doLoad(std::shared_ptr<PlayerSession> ps, const std::string& buf) {
    LOG(INFO) << "RankServlet doLoad";
    Protocol::C2S_RankLoad reqMsg;
    if (!reqMsg.ParseFromString(buf)) {
        return false;
    }

    Protocol::S2C_RankLoad resMsg;
    auto role = ps->role();
    int limit = ServerResource::get()->serverConfig()->rankLimit();
    std::map<long long, int> ranks;
    ServerResource::get()->rcPool()->zrevrange(ranks, RedisKey::Rank(reqMsg.game_id()), 0, limit);

    std::set<long long> ids;
    for (auto it = ranks.begin(); it != ranks.end(); ++it) {
        ids.insert(it->first);
    }

    std::map<long long, Role::ptr> roles;
    AccountManager::listRoles(roles, reqMsg.game_id(), ids);
    int index = 0;
    for (auto it = ranks.begin(); it != ranks.end(); ++it) {
        auto it1 = roles.find(it->first);
        if (it1 == roles.end() || !it1->second) {
            continue;
        }

        Role::ptr role = it1->second;
        Protocol::RankItem* ri = resMsg.add_ris();
        ri->set_rank(++index);
        ri->set_role_id(role->roleId());
        ri->set_name(role->name());
        ri->set_avatarurl(role->avatarurl());
    }
    ps->send(Protocol::MsgId::S2C_RANK_LOAD, resMsg);

    return true;
}

bool RankServlet::doUpdate(std::shared_ptr<PlayerSession> ps, const std::string& buf) {
    LOG(INFO) <<"RankServlet doUpdate";
    Protocol::C2S_RankUpdate reqMsg;
    if (buf.empty() || !reqMsg.ParseFromString(buf)) {
        return false;
    }

    Protocol::S2C_RankUpdate resMsg;
    auto role = ps->role();
    int score = ServerResource::get()->rcPool()->zscore(RedisKey::Rank(reqMsg.game_id()), role->roleId());
    if (reqMsg.score() > score) {
        ServerResource::get()->rcPool()->zadd(RedisKey::Rank(reqMsg.game_id()), (int)reqMsg.score(), role->roleId());
    }

    ps->send(Protocol::MsgId::S2C_RANK_UPDATE, resMsg);

    role->timerField()->add(TimerField::TTF_PASS_LEVEL_NUM);
    role->timerField()->flushToCache(reqMsg.game_id(), role->roleId());
    auto num = role->timerField()->get(TimerField::TTF_PASS_LEVEL_NUM);
    if (num % 10 == 0) {
        ServerResource::get()->marqueeManager()->notifyMarquee(role->gameId(), MarqueeManager::MT_PASS_LEVEL, role->name(), num);
    }

    return true;
}
