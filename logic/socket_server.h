#ifndef __LOGIC_SOCKET_SERVER_H__
#define __LOGIC_SOCKET_SERVER_H__

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>

class SocketServer {
public:
    void run();

private:
    void dailyReset();

    void notifyRankTimer();

    void printGoInfo(int i);
};

#endif