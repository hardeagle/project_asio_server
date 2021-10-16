#ifndef __LOGIC_ROLE_INFO_H__
#define __LOGIC_ROLE_INFO_H__

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>

#include "logic/database/database.pb.h"

class TimerField;

class Role {
friend class AccountManager;
friend class PlayerSession;
public:
    typedef std::shared_ptr<Role> ptr;

    Role();

    void roleId(long long v) { m_proto.set_role_id(v); }
    long long roleId() const { return m_proto.role_id(); }

    void gameId(int v) { m_proto.set_game_id(v); }
    int gameId() const { return m_proto.game_id(); }

    void openid(const std::string& v) { m_proto.set_openid(v); }
    const std::string& openid() const { return m_proto.openid(); }

    void name(const std::string& v) { m_proto.set_name(v); }
    const std::string& name() const { return m_proto.name(); }

    void avatarurl(const std::string& v) { m_proto.set_avatarurl(v); }
    const std::string& avatarurl() const { return m_proto.avatarurl(); }

    void country(const std::string& v) { m_proto.set_country(v); }
    const std::string& country() const { return m_proto.country(); }

    void city(const std::string& v) { m_proto.set_city(v); }
    const std::string& city() const { return m_proto.city(); }

    void createTime(int v) { m_proto.set_create_time(v); }
    int createTime() const { return m_proto.create_time(); }

    void loginTime(int v) { m_proto.set_login_time(v); }
    int logintime() const { return m_proto.login_time(); }

    void logoutTime(int v) { m_proto.set_logout_time(v); }
    int logoutTime() const { return m_proto.logout_time(); }

    void dailyResetTime(int v) { m_proto.set_daily_reset_time(v); }
    int dailyResetTime() const { return m_proto.daily_reset_time(); }

    void doLogin();
    void doLogout();

    void dailyReset();

    std::shared_ptr<TimerField> timerField() { return m_timerField;}

    void flushToCache();

    static ptr loadFromCache(int game_id, long long role_id);
    static ptr create();

private:
    Database::Role m_proto;

    std::shared_ptr<TimerField> m_timerField;
};

#endif