#ifndef __LOGIC_PLAYER_SESSION_H__
#define __LOGIC_PLAYER_SESSION_H__

#include <memory>

#include "log/glog.h"
#include "net/ws_connection.h"
#include "net/connection.h"

class Role;

class Player {
friend class PlayerSessionManager;
public:
    typedef std::shared_ptr<Player> ptr;

    void role(std::shared_ptr<Role> role) {
        m_role = role;
    }

    std::shared_ptr<Role> role() {
        return m_role;
    }

    void doLogin();
    void doLogout();

    void dailyReset();

private:
    std::shared_ptr<Role> m_role;
};


class PlayerSession : public Player, virtual public Session {
public:
    typedef std::shared_ptr<PlayerSession> ptr;

    PlayerSession();
    ~PlayerSession();
};



class WebSocketPlayerSession : public WsConnection, public PlayerSession {
public:
    typedef std::shared_ptr<WebSocketPlayerSession> ptr;

    WebSocketPlayerSession(boost::asio::io_context &io_context, Resource::ptr resource)
        : WsConnection(io_context, resource) {
    }

private:

};



class SocketPlayerSession : public Connection, public PlayerSession {
public:
    typedef std::shared_ptr<SocketPlayerSession> ptr;

    SocketPlayerSession(boost::asio::io_context &io_context, boost::asio::ssl::context& ssl_context)
        : Connection(io_context, ssl_context) {
    }

private:

};

#endif