#ifndef __LOGIC_SERVLET_ACCOUNT_SERVLET_H__
#define __LOGIC_SERVLET_ACCOUNT_SERVLET_H__

#include "net/servlet.h"


class PlayerSession;

class AccountServlet : public Servlet {
public:
    virtual bool doRequest(Session::ptr session, uint16_t id, const std::string& buf) override;

private:
    bool doLogin(std::shared_ptr<PlayerSession> ps, const std::string& buf);
    bool doCreate(std::shared_ptr<PlayerSession> ps, const std::string& buf);
    bool doLoad(std::shared_ptr<PlayerSession> ps, const std::string& buf);
    bool doAskOpenid(std::shared_ptr<PlayerSession> ps, const std::string& buf);
    bool doUpdate(std::shared_ptr<PlayerSession> ps, const std::string& buf);
};

#endif