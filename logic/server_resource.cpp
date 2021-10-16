#include "server_resource.h"

#include "logic/marquee_manager.h"
#include "logic/player_session_manager.h"
#include "logic/server_config.h"
#include "logic/timer_manager.h"
#include "redis/redis.h"

void ServerResource::init(boost::asio::io_context& ioc) {
    m_marqueeManager = std::make_shared<MarqueeManager>();

    m_psMgr = std::make_shared<PlayerSessionManager>();

    m_rcPool = std::make_shared<RedisConnectionPool>(ioc);
    m_rcPool->init();

    m_serverConfig = std::make_shared<ServerConfig>();
    m_serverConfig->init();

    m_timerManager = std::make_shared<TimerManager>();
    m_timerManager->tick();
}