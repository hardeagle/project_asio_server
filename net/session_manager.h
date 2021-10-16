
#ifndef __NET_SESSION_MANAGER_H__
#define __NET_SESSION_MANAGER_H__

#include <unordered_set>
#include <memory>

#include <boost/asio.hpp>

#include "session.h"

// template <typename T>
// class SessionManager {
// public:
//     typedef std::shared_ptr<SessionManager<T>> ptr;

//     //SessionManager(const SessionManager&) = delete;
//     //SessionManager& operator=(const SessionManager&) = delete;

//     std::shared_ptr<T> create(boost::asio::io_context &ioContext);
//     void release(const std::shared_ptr<T> &session);

// private:
//     std::unordered_set<std::shared_ptr<T>> m_sessions;
// };



// template <typename T>
// std::shared_ptr<T> SessionManager<T>::create(boost::asio::io_context &ioContext) {
//     auto session = std::make_shared<T>(ioContext);
//     m_sessions.insert(session);
//     return session;
// }

// template <typename T>
// void SessionManager<T>::release(const std::shared_ptr<T> &session) {
//     m_sessions.erase(session);
// }

class SessionManager {
public:
    typedef std::shared_ptr<SessionManager> ptr;

    virtual void handleConnect(Session::ptr session) {
    }

    virtual void handleDisconnect(Session::ptr session) {
    }

private:
};

#endif