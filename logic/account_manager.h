#ifndef __LOGIC_ACCOUNT_MANAGER_H__
#define __LOGIC_ACCOUNT_MANAGER_H__

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>

#include "logic/redis_key.h"
#include "logic/id_generator.h"
#include "logic/role.h"
#include "logic/server_resource.h"
#include "redis/redis.h"


class AccountManager {
public:

    static long long roleId(int game_id, const std::string& openid) {
        long long roleId = 0;
        ServerResource::get()->rcPool()->hget(roleId, RedisKey::Account(game_id), openid);
        return roleId;
    }

    static void roleId(int game_id, const std::string& openid, long long roleId) {
        ServerResource::get()->rcPool()->hset(RedisKey::Account(game_id), openid, roleId);
    }

    static Role::ptr parse(const std::string& serial) {
        auto role = std::make_shared<Role>();
        role->m_proto.ParseFromString(serial);
        return role;
    }

    static void listRoles(std::map<long long, Role::ptr>& roles, int game_id, const std::set<long long>& ids) {
        std::list<std::string> serializes;
        ServerResource::get()->rcPool()->hmget(serializes, RedisKey::Role(game_id), ids);
        for (auto it = serializes.begin(); it != serializes.end(); ++it) {
            auto role = parse(*it);
            roles[role->roleId()] = role;
        }
    }
};

#endif