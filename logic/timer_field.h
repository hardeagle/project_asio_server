#ifndef __LOGIC_TIMER_FIELD__
#define __LOGIC_TIMER_FIELD__

#include <memory>
#include <vector>

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>

#include "logic/database/database.pb.h"

class TimerField {
public:
    typedef std::shared_ptr<TimerField> ptr;

    enum {
        TTF_BASE = 0,
        TTF_PASS_LEVEL_NUM,
        TTF_TOP,
    };

    TimerField();

    int get(int type);
    void add(int type, int num = 1);

    void dailyReset();

    void loadFromCache(int game_id, long long role_id);
    void flushToCache(int game_id, long long role_id);

private:
    Database::TimerField m_proto;
    std::vector<int> m_tfs;
};

#endif