#include "socket_server.h"

#include <stdio.h>
#include <unistd.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "log/glog.h"
#include "net/connection.h"
#include "net/server_manager.h"
#include "net/ws_connection.h"
#include "net/https_request.h"
#include "redis/redis.h"

#include "logic/marquee_manager.h"
#include "logic/player_session.h"
#include "logic/player_session_manager.h"
#include "logic/protocol/protocol_id.pb.h"
#include "logic/redis_key.h"
#include "logic/role.h"
#include "logic/server_resource.h"
#include "logic/servlet/account_servlet.h"
#include "logic/servlet/rank_servlet.h"
#include "logic/servlet/shop_servlet.h"
#include "logic/servlet/system_servlet.h"
#include "logic/timer_manager.h"
#include "logic/util.h"

template <typename T>
static void setupServlet(T server) {
    server->registerDisconnect(std::bind(&PlayerSessionManager::handleDisConnect, ServerResource::get()->psMgr(), std::placeholders::_1));

    server->template addServlet<SystemServlet>(Protocol::MsgId::C2S_SYSTEM_BASE, Protocol::MsgId::C2S_SYSTEM_TOP);
    server->template addServlet<AccountServlet>(Protocol::MsgId::C2S_ACCOUNT_BASE, Protocol::MsgId::C2S_ACCOUNT_TOP);
    server->template addServlet<ShopServlet>(Protocol::MsgId::C2S_SHOP_BASE, Protocol::MsgId::C2S_SHOP_TOP);
    server->template addServlet<RankServlet>(Protocol::MsgId::C2S_RANK_BASE, Protocol::MsgId::C2S_RANK_TOP);
}

void SocketServer::run() {
    boost::asio::io_context ioc{8};

    ServerResource::ptr res = ServerResource::get();
    res->init(ioc);

    res->timerManager()->addDailyTimer(0, 0, 0, std::bind(&SocketServer::dailyReset, this));

    res->timerManager()->addHourlyTimer(30, 0, std::bind(&SocketServer::printGoInfo, this, 300));

    //res->timerManager()->addMinuteTimer(37, std::bind(&SocketServer::printGoInfo, this, 1000));

    //res->timerManager()->addIntervalTimer(6000, std::bind(&SocketServer::notifyRankTimer, this));

    //res->timerManager()->addIntervalTimer(3000, std::bind(&SocketServer::printGoInfo, this, 1000));

    // for (int i = 0; i <= 60; i += 2) {
    //     res->timerManager()->addMinuteTimer(i, std::bind(&SocketServer::printGoInfo, this, i));
    // }

    

    ServerManager sm(ioc);
    setupServlet(sm.addServer<WebSocketPlayerSession>(9117));
    //setupServlet(sm.addServer<SocketPlayerSession>(9119));
    sm.run();

    //co_sched.Start(1, 8);
}

void SocketServer::dailyReset() {
    LOG(WARNING) << "dailyReset " << getCurrentSecond();

    std::list<PlayerSession::ptr> pss;
    ServerResource::get()->psMgr()->listOnlinePlayers(pss);
    for (auto it = pss.begin(); it != pss.end(); ++it) {
        (*it)->dailyReset();
    }
}

void SocketServer::notifyRankTimer() {
    LOG(WARNING) << "notifyRankTimer " << getCurrentSecond();
    std::map<int, std::string> games;
    ServerResource::get()->rcPool()->hgetall(games, RedisKey::Game());
    for (auto it = games.begin(); it != games.end(); ++it) {
        int rank = 0;
        std::map<long long, int> ranks;
        ServerResource::get()->rcPool()->zrevrange(ranks, RedisKey::Rank(it->first), 0, 2);
        for (auto it1 = ranks.begin(); it1 != ranks.end(); ++it1) {
            Role::ptr role = Role::loadFromCache(it->first, it1->first);
            ServerResource::get()->marqueeManager()->notifyMarquee(role->gameId(), MarqueeManager::MT_RANK, role->name(), it1->second, ++rank);
        }
    }
}

void SocketServer::printGoInfo(int i) {
    LOG(ERROR) << "--------------------------------------------------------------slot timer-------------, i " << i;
    // LOG(ERROR) << "---------print go info begin---------";
    // LOG(ERROR) << "TaskCount " << co_sched.TaskCount();
    // LOG(ERROR) << "GetCurrentTaskID " << co_sched.GetCurrentTaskID();
    // LOG(ERROR) << "GetCurrentTaskYieldCount " << co_sched.GetCurrentTaskYieldCount();
    // LOG(ERROR) << "---------print go info end---------\r\n" << std::endl;
}
