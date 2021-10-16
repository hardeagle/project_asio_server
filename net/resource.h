#ifndef __NET_RESOURCE_H__
#define __NET_RESOURCE_H__

#include <memory>

#include "scheduler.h"
#include "servlet.h"

//class Scheduler;
//class Servlet;

class Resource {
public:
    typedef std::shared_ptr<Resource> ptr;

    Resource() {
        m_scheduler = std::make_shared<Scheduler>(8);
        m_servlet = std::make_shared<ServletDispatchRange>();
    }

    std::shared_ptr<Scheduler> scheduler() { return m_scheduler; }

    std::shared_ptr<ServletDispatchRange> servlet() { return m_servlet; }

private:
    std::shared_ptr<Scheduler> m_scheduler;
    std::shared_ptr<ServletDispatchRange> m_servlet;
};

#endif