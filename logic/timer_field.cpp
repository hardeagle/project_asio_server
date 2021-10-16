#include "timer_field.h"

#include <string>

#include "redis/redis.h"

#include "logic/redis_key.h"
#include "logic/server_resource.h"


TimerField::TimerField() {
    m_tfs.resize(TTF_TOP, 0);
}

int TimerField::get(int type) {
    if (type > TTF_BASE && type < TTF_TOP) {
        return m_tfs[type];
    }
    return 0;
}

void TimerField::add(int type, int val) {
    if (type > TTF_BASE && type < TTF_TOP) {
        m_tfs[type] += val;
    }
}

void TimerField::dailyReset() {
    for (size_t i = 0; i < m_tfs.size(); ++i) {
        m_tfs[i] = 0;
    }
}

void TimerField::loadFromCache(int game_id, long long role_id) {
    std::string serial;
    ServerResource::get()->rcPool()->hget(serial, RedisKey::TimerField(game_id), role_id);
    m_proto.ParseFromString(serial);

    for (auto i = 0; i < m_proto.tfs_size(); ++i) {
        if (m_proto.tfs(i).key() > 0 && m_proto.tfs(i).key() < (int)m_tfs.size()) {
            m_tfs[m_proto.tfs(i).key()] = m_proto.tfs(i).val();
        }
    }
}

void TimerField::flushToCache(int game_id, long long role_id) {
    m_proto.clear_tfs();
    for (size_t i = 0; i < m_tfs.size(); ++i) {
        Database::MapII* tf = m_proto.add_tfs();
        tf->set_key(i);
        tf->set_val(m_tfs[i]);
    }

    std::string serial;
    m_proto.SerializeToString(&serial);
    ServerResource::get()->rcPool()->hset(RedisKey::TimerField(game_id), role_id, serial);
}