
#include "servlet.h"

#include "log/glog.h"

static int count = 0;

bool ServletDispatchRange::Element::operator < (const Element &element) const {
    return to < element.to;
}

bool ServletDispatchRange::doRequest(std::shared_ptr<Session> conn, uint16_t id, const std::string &buf) {
    LOG(INFO) << "ServletDispatcher doRequest id: " << id;

    auto it = m_servlets.lower_bound(Element(id));
    if (it == m_servlets.end()) {
        LOG(WARNING) << "over dispatcher, id " << id;
    } else if (id >= it->from && id <= it->to) {
        count++;
        if (count % 10000 == 0) {
            LOG(ERROR) << "-------------------------------------------------count " << count;
        }
        return it->servlet->doRequest(conn, id, buf);
    } else {
        LOG(WARNING) << "wtf? id " << id;
    }

    return true;
 }