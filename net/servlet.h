
#ifndef __NET_SERVLET_H__
#define __NET_SERVLET_H__

#include <memory>
#include <set>

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>

#include "session.h"

class Servlet {
public:
    typedef std::shared_ptr<Servlet> ptr;

    virtual ~Servlet() {}

    virtual bool doRequest(Session::ptr conn, uint16_t id, const std::string &buf) {
        return true;
    }
};


class ServletDispatchRange {
public:
    typedef std::shared_ptr<ServletDispatchRange> ptr;

    struct Element {
        Element(uint16_t f)
            : from(f)
            , to(f) {
        }

        Element(uint16_t f, uint16_t t, Servlet::ptr servlet)
            : from(f)
            , to(t)
            , servlet(servlet) {
        }

        bool operator < (const Element &element) const;

        uint16_t from;
        uint16_t to;
        Servlet::ptr servlet;
    };

    void addServlet(uint16_t from, uint16_t to, Servlet::ptr servlet) {
        Element element(from, to, servlet);
        m_servlets.insert(element);
    }

    bool doRequest(std::shared_ptr<Session> conn, uint16_t id, const std::string &buf);

private:
    std::set<Element> m_servlets;
};

#endif