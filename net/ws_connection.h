
#ifndef __NET_WS_CONNECTION_H__
#define __NET_WS_CONNECTION_H__

#include <deque>
#include <list>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>

#include "log/glog.h"

#include "buffer.h"
#include "session.h"
#include "resource.h"

namespace google {
namespace protobuf {
    class Message;
}}

class ServletDispatchRange;
class Resource;

class WebSocketStream {
public:
    typedef std::shared_ptr<WebSocketStream> ptr;

    WebSocketStream(boost::asio::ip::tcp::socket &&socket)
        : m_wss(std::move(socket)) {
    }

    boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& wss() {
        return m_wss;
    }

private:
    boost::beast::websocket::stream<boost::asio::ip::tcp::socket> m_wss;
};

class WsConnection : virtual public Session {
public:
    typedef std::shared_ptr<WsConnection> ptr;

    WsConnection(const WsConnection&) = delete;
    WsConnection& operator=(const WsConnection&) = delete;

    WsConnection(boost::asio::io_context& ioc, Resource::ptr resource)
        : m_ioc(ioc)
        , m_strand(boost::asio::make_strand(ioc))
        , m_socket(ioc)
        , m_resource(resource) {
    }

    virtual ~WsConnection() {
    }

    boost::asio::ip::tcp::socket& getSocket() {
        return m_socket;
    }

    void run();

    void send(uint16_t id, google::protobuf::Message& msg);
    void send(uint16_t id, const std::string& msg);

private:
    WsConnection::ptr shared_from_self() {
        return std::dynamic_pointer_cast<WsConnection>(shared_from_this());
    }

    boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& wss() {
        return m_wss->wss();
    }

    void setupWss();

    void doRead();
    void doWrite();

    void close();

private:
    boost::asio::io_context& m_ioc;
    boost::asio::strand<boost::asio::io_context::executor_type> m_strand;
    boost::asio::ip::tcp::socket m_socket;
    WebSocketStream::ptr m_wss;

    std::deque<Buffer> m_wMsgs;

    std::shared_ptr<ServletDispatchRange> m_servlet;

    std::shared_ptr<Resource> m_resource;

    boost::beast::flat_buffer m_buffer;
};

#endif