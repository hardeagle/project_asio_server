
#ifndef __NET_SESSION_H__
#define __NET_SESSION_H__

#include <functional>
#include <memory>
#include <string>

namespace google {
namespace protobuf {
    class Message;
}}

class Session;

typedef std::function<void(std::shared_ptr<Session> session)> Func;

class Session : public std::enable_shared_from_this<Session> {
public:
    typedef std::shared_ptr<Session> ptr;

    virtual ~Session() {}

    virtual void send(uint16_t id, google::protobuf::Message& msg) {}
    virtual void send(uint16_t id, const std::string& msg) {}

    void registerDisconnect(Func func) {
        m_func = func;
    }

protected:
    Func m_func;
};

#endif