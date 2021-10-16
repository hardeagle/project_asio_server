#ifndef __LOGIC_SERVLET_SYSTEM_SERVLET_H__
#define __LOGIC_SERVLET_SYSTEM_SERVLET_H__

#include "net/servlet.h"


class PlayerSession;

class SystemServlet : public Servlet {
public:
    virtual bool doRequest(Session::ptr session, uint16_t id, const std::string &buf) override;

private:
    bool doTick(std::shared_ptr<PlayerSession> ps, const std::string &buf);
};

#endif