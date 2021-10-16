
#ifndef __NET_SERVER_MANAGER_H__
#define __NET_SERVER_MANAGER_H__

#include <memory>
#include <unordered_map>

#include <boost/asio.hpp>

#include "log/glog.h"

#include "servlet.h"
#include "server.h"

class ServerManager {
public:
    ServerManager(boost::asio::io_context& ioc)
        : m_ioc(ioc) {
    }
    ~ServerManager() {}

    ServerManager(const ServerManager&) = delete;
    ServerManager& operator=(const ServerManager&) = delete;

    void run() {
        //m_ioc.run();

        m_threads.reserve(8 - 1);
        for(auto i = 8 - 1; i > 0; --i)  {
            LOG(ERROR) << "i " << i;
            m_threads.emplace_back([this] {
                m_ioc.run();
            });
        }
        LOG(ERROR) << "size " << m_threads.size();
        m_ioc.run();
    }

    void stop() {
        m_ioc.stop();
    }

    template <typename T>
    std::shared_ptr<Server<T>> addServer(uint16_t port) {
        if (port == 0) {
            LOG(ERROR) << "add fail, port " << port;
            return std::shared_ptr<Server<T>>();
        }
        if (m_servers.find(port) != m_servers.end()) {
            LOG(ERROR) << "add fail, port had listened, port " << port;
            return std::shared_ptr<Server<T>>();
        }
        auto server = std::make_shared<Server<T>>(m_ioc);
        server->open(port);
        m_servers[port] = server;

        return server;
    }

private:
    boost::asio::io_context& m_ioc;
    std::vector<std::thread> m_threads;

    std::unordered_map<uint16_t, std::shared_ptr<BaseServer>> m_servers;
};

#endif
