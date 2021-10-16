#ifndef __NET_CONNECTION_H__
#define __NET_CONNECTION_H__

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <memory>

#include "session.h"

namespace google {
namespace protobuf {
    class Message;
}}

class ServletDispatchRange;

class Connection : virtual public Session {
public:
    typedef std::shared_ptr<Connection> ptr;

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(boost::asio::io_context &ioContext, boost::asio::ssl::context& ctx)
        : m_socket(ioContext) {
    }

    ~Connection() {}

    boost::asio::ip::tcp::socket& getSocket() {
        return m_socket;
    }

    void run(std::shared_ptr<ServletDispatchRange> servlet);

    void send(uint16_t id, google::protobuf::Message& msg) {}
    void send(uint16_t id, const std::string& msg) {}


private:
    Connection::ptr shared_from_self() {
        return std::dynamic_pointer_cast<Connection>(shared_from_this());
    }

    void read();
    void write();

private:
    boost::asio::ip::tcp::socket m_socket;

    std::shared_ptr<ServletDispatchRange> m_servlet;
};

#endif