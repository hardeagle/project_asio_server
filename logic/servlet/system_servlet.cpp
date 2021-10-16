#include "system_servlet.h"

#include "log/glog.h"

#include "logic/player_session.h"
#include "logic/protocol/protocol_id.pb.h"
#include "logic/protocol/protocol_system.pb.h"


bool SystemServlet::doRequest(Session::ptr session, uint16_t id, const std::string &buf) {
    auto ps = std::dynamic_pointer_cast<PlayerSession>(session);
    switch (id) {
        case Protocol::MsgId::C2S_SYSTEM_TICK:
            return doTick(ps, buf);
    }

    return true;
}


bool SystemServlet::doTick(std::shared_ptr<PlayerSession> ps, const std::string &buf) {
    LOG(INFO) << "SystemServlet doSystemTick";

    Protocol::S2C_SystemTick resMsg;
    ps->send(Protocol::MsgId::S2C_SYSTEM_TICK, resMsg);

    return true;
}
