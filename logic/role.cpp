#include "role.h"

#include "log/glog.h"
#include "redis/redis.h"

#include "logic/id_generator.h"
#include "logic/server_resource.h"
#include "logic/redis_key.h"
#include "logic/timer_field.h"
#include "logic/util.h"

Role::Role() {
    createTime(getCurrentSecond());

    m_timerField = std::make_shared<TimerField>();
}

void Role::doLogin() {
    loginTime(getCurrentSecond());

    if (!isToday(dailyResetTime())) {
        dailyReset();
    }
}

void Role::doLogout() {
    logoutTime(getCurrentSecond());
}

void Role::dailyReset() {
    dailyResetTime(getCurrentSecond());

    timerField()->dailyReset();
}

void Role::flushToCache() {
    std::string data;
    m_proto.SerializeToString(&data);
    ServerResource::get()->rcPool()->hset(RedisKey::Role(gameId()), roleId(), data);
}

Role::ptr Role::create() {
    Role::ptr role = std::make_shared<Role>();
    role->roleId(IdGenerator::roleId());

    return role;
}

Role::ptr Role::loadFromCache(int game_id, long long role_id) {
    std::string data;
    auto ret = ServerResource::get()->rcPool()->hget(data, RedisKey::Role(game_id), role_id);
    if (!ret) {
        LOG(ERROR) << "hget fail, role_id " << role_id;
        return Role::ptr();
    }

    Role::ptr role = std::make_shared<Role>();
    if (data.empty() || !role->m_proto.ParseFromString(data)) {
        LOG(ERROR) << "parse fail, role id " << role_id << "\t data: " << data;
        return Role::ptr();
    }

    role->timerField()->loadFromCache(game_id, role_id);

    return role;
}
