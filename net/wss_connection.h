
#ifndef __NET_WSS_CONNECTION_H__
#define __NET_WSS_CONNECTION_H__

#include <list>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>

#include "buffer.h"
#include "session.h"

namespace google {
namespace protobuf {
    class Message;
}}

class ServletDispatchRange;

class WebSocketSslStream {
public:
    typedef std::shared_ptr<WebSocketSslStream> ptr;

    WebSocketSslStream(boost::asio::ip::tcp::socket &&socket, boost::asio::ssl::context& ctx)
        : m_wss(std::move(socket), ctx) {
    }

    //boost::beast::websocket::stream<boost::beast::tcp_stream>& wss() {
    //boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& wss()
    boost::beast::websocket::stream<boost::beast::ssl_stream<boost::asio::ip::tcp::socket>>& wss(){
        return m_wss;
    }

private:
    //boost::beast::websocket::stream<boost::beast::tcp_stream> m_wss;
    //boost::beast::websocket::stream<boost::asio::ip::tcp::socket> m_wss;
    boost::beast::websocket::stream<boost::beast::ssl_stream<boost::asio::ip::tcp::socket>> m_wss;
};

class WssConnection : virtual public Session {
public:
    typedef std::shared_ptr<WssConnection> ptr;

    WssConnection(const WssConnection&) = delete;
    WssConnection& operator=(const WssConnection&) = delete;

    WssConnection(boost::asio::io_context& io_context, boost::asio::ssl::context& ssl_context)
        : m_sslContext(ssl_context)
        , m_socket(io_context) {
    }

    ~WssConnection() {
    }

    boost::asio::ip::tcp::socket& getSocket() {
        return m_socket;
    }

    void run(std::shared_ptr<ServletDispatchRange> servlet);

    void send(uint16_t id, google::protobuf::Message& msg);
    void send(uint16_t id, const std::string& msg);

private:
    WssConnection::ptr shared_from_self() {
        return std::dynamic_pointer_cast<WssConnection>(shared_from_this());
    }

    //boost::beast::websocket::stream<boost::beast::tcp_stream>& wss() {
    //boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& wss() {
    boost::beast::websocket::stream<boost::beast::ssl_stream<boost::asio::ip::tcp::socket>>& wss() {
        return m_wss->wss();
    }

    void setupWss();

    void read();
    void write();

    void close();

private:
    boost::asio::ssl::context& m_sslContext;
    boost::asio::ip::tcp::socket m_socket;
    WebSocketSslStream::ptr m_wss;

    std::shared_ptr<ServletDispatchRange> m_servlet;

    //co::Channel<Buffer> m_wChannel;

    //co_mutex m_mutex;
};

#endif