#ifndef __LOGIC_PLAYER_SESSION_MANAGER_H__
#define __LOGIC_PLAYER_SESSION_MANAGER_H__

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>

#include <libgo/coroutine.h>

#include "log/glog.h"

#include "logic/player_session.h"

namespace google {
namespace protobuf {
    class Message;
}}

class Session;
//class PlayerSession;

class PlayerSessionManager {
public:
    typedef std::shared_ptr<PlayerSessionManager> ptr;

    std::shared_ptr<PlayerSession> getPlayer(int game_id, long long roleId);
    void listOnlinePlayers(std::list<std::shared_ptr<PlayerSession> >& pss);
    void listOnlinePlayers(int game_id, std::list<std::shared_ptr<PlayerSession>>& pss);

    void playerOnline(std::shared_ptr<PlayerSession> ps);
    void playerOffline(std::shared_ptr<PlayerSession> ps);

    std::shared_ptr<PlayerSession> loadPlayerFromCache(int game_id, long long roleId);

    void handleDisConnect(std::shared_ptr<Session> session);

    void broadcast(int game_id, uint16_t id, google::protobuf::Message& msg);

private:
    std::mutex m_mutex;
    std::map<long long, std::shared_ptr<PlayerSession>> m_onlinePlayers;
    std::map<int, std::map<long long, std::shared_ptr<PlayerSession>>> m_goPlayers;
};

#endif