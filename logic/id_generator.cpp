#include "id_generator.h"

#include <string>

#include "logic/server_resource.h"
#include "redis/redis.h"

long long IdGenerator::nextId(const std::string& field) {
    std::string key = "eayew_id_" + m_zoneId;
    long long id = 0;
    ServerResource::get()->rcPool()->hincrby(id, key, field);
    return id;
}

long long IdGenerator::roleId() {
    long long next_id = nextId("role_id");
    if (next_id <= 0) {
        return 0;
    }
    return m_zoneId << 24 | (next_id & 0xffffff);
}