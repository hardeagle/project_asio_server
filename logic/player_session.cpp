#include "player_session.h"

#include "log/glog.h"

#include "logic/id_generator.h"
#include "logic/role.h"
#include "logic/server_resource.h"

static int count = 0;

void Player::doLogin() {
    if (!m_role) {
        return;
    }

    m_role->doLogin();
}

void Player::doLogout() {
    if (!m_role) {
        return;
    }

    m_role->doLogout();
}

void Player::dailyReset() {
    if (!m_role) {
        return;
    }

    m_role->dailyReset();
}

PlayerSession::PlayerSession() {
    ++count;
    LOG(ERROR) << "---PlayerSession count " << count;
}

PlayerSession::~PlayerSession() {
    --count;
    LOG(ERROR) << "---~PlayerSession count " << count;
}
