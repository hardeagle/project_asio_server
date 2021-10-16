#ifndef __NET_SERVER_H__
#define __NET_SERVER_H__

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>

#include "log/glog.h"

#include "resource.h"
#include "servlet.h"
#include "session_manager.h"

//typedef std::function<void(std::shared_ptr<Session> session)> Func;

class BaseServer {
public:
    typedef std::shared_ptr<BaseServer> ptr;

    virtual void open(uint16_t port) {}

    //virtual void addServlet(uint16_t from, uint16_t to, Servlet::ptr servlet) {}
};

template <typename T>
class Server : public BaseServer {
public:
    typedef std::shared_ptr<Server<T>> ptr;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    explicit
    Server(boost::asio::io_context &ioContext)
        : m_ioContext(ioContext)
        , m_sslContext(boost::asio::ssl::context::tlsv12) {
        //m_servlet = std::make_shared<ServletDispatchRange>();
        //m_sessionManager = std::make_shared<SessionManager<T>>();
        m_resource = std::make_shared<Resource>();
    }

    ~Server() {}


    void doAccept() {
        std::shared_ptr<T> session = std::make_shared<T>(m_ioContext, m_resource);
        m_acceptor->async_accept(session->getSocket(), [this, session](const boost::system::error_code& ec) {
            if (!ec) {
                session->registerDisconnect(m_func);
                session->run();
            }
            doAccept();
        });
    }

    void open(uint16_t port) {
        m_port = port;

        //loadServerCertificate(m_sslContext);

        try {
            m_acceptor.reset(new boost::asio::ip::tcp::acceptor(m_ioContext,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::address(
                    boost::asio::ip::address_v4(INADDR_ANY)), m_port)));
            m_acceptor->set_option(boost::asio::ip::tcp::no_delay(true));

            doAccept();
        } catch(boost::system::system_error& e) {
        }
    }

    void close() {
        //m_acceptor->close(ec);
    }

    //template<template<typename> class U>
    template<class U>
    void addServlet(uint16_t from, uint16_t to) {
        //auto servlet = std::make_shared<U<T>>();
        auto servlet = std::make_shared<U>();
        m_resource->servlet()->addServlet(from, to, servlet);
    }

    void registerDisconnect(Func func) {
        m_func = func;
    }

private:
    void loadServerCertificate(boost::asio::ssl::context& ctx) {
        ctx.set_password_callback([](std::size_t, boost::asio::ssl::context_base::password_purpose){
            return "co_server";
        });

        ctx.set_options(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2);

        ctx.use_certificate_chain_file("www.eayew.com.pem");
        ctx.use_private_key_file("www.eayew.com.key", boost::asio::ssl::context::pem);
    }

private:
    boost::asio::io_context& m_ioContext;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;

    boost::asio::ssl::context m_sslContext;

    uint16_t m_port = 0;
    //ServletDispatchRange::ptr m_servlet;
    //std::shared_ptr<SessionManager<T>> m_sessionManager;

    Resource::ptr m_resource;

    Func m_func;
};

#endif