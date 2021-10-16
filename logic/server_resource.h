#ifndef __LOGIC_SERVER_RESOURCE_H__
#define __LOGIC_SERVER_RESOURCE_H__

#include <memory>

#include "log/glog.h"
#include "net/connection.h"
#include "net/server_manager.h"
#include "net/ws_connection.h"
#include "net/https_request.h"
#include "redis/redis.h"

class MarqueeManager;
class PlayerSessionManager;
class RedisConnectionPool;
class ServerConfig;
class TimerManager;

class ServerResource {
public:
    typedef std::shared_ptr<ServerResource> ptr;

    static ptr get() {
        static ptr res = std::make_shared<ServerResource>();
        return res;
    }

    void init(boost::asio::io_context& ioc);

    std::shared_ptr<MarqueeManager> marqueeManager() { return m_marqueeManager; }

    std::shared_ptr<PlayerSessionManager> psMgr() { return m_psMgr; }

    std::shared_ptr<RedisConnectionPool> rcPool() { return m_rcPool; }

    std::shared_ptr<ServerConfig> serverConfig() { return m_serverConfig; }

    std::shared_ptr<TimerManager> timerManager() { return m_timerManager; }

// private:
//     ServerResource() {}

private:
    std::shared_ptr<MarqueeManager> m_marqueeManager;
    std::shared_ptr<PlayerSessionManager> m_psMgr;
    std::shared_ptr<RedisConnectionPool> m_rcPool;
    std::shared_ptr<ServerConfig> m_serverConfig;
    std::shared_ptr<TimerManager> m_timerManager;
};

#endif