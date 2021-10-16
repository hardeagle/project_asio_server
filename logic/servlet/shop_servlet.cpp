#include "shop_servlet.h"

#include "log/glog.h"

#include "logic/player_session.h"
#include "logic/protocol/protocol_id.pb.h"
#include "logic/protocol/protocol_shop.pb.h"


bool ShopServlet::doRequest(Session::ptr session, uint16_t id, const std::string &buf) {
    auto ps = std::dynamic_pointer_cast<PlayerSession>(session);
    switch (id) {
        case Protocol::MsgId::C2S_SHOP_LOAD:
            return doLoad(ps, buf);
        case Protocol::MsgId::C2S_SHOP_BUY:
            return doBuy(ps, buf);
    }

    return true;
}


bool ShopServlet::doLoad(std::shared_ptr<PlayerSession> ps, const std::string &buf) {
    LOG(INFO) << "ShopServlet doLoad";
    return true;
}

bool ShopServlet::doBuy(std::shared_ptr<PlayerSession> ps, const std::string &buf) {
    LOG(INFO) << "ShopServlet doBuy";
    return true;
}
