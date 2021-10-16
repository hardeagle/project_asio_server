#include "timer_manager.h"

#include <chrono>
#include <sys/time.h>
#include <thread>

#include "log/glog.h"

static const int COEF = 1000;
static const int MINUTE = 60;
static const int HOUR = 60 * 60;
static const int LAG = 8 * 60 * 60;
static const int DAY = 24 * 60 * 60;

#define TVN_BITS 6
#define TVR_BITS 8
#define TVN_SIZE (1 << TVN_BITS)
#define TVR_SIZE (1 << TVR_BITS)
#define TVN_MASK (TVN_SIZE - 1)
#define TVR_MASK (TVR_SIZE - 1)
#define OFFSET(N) (TVR_SIZE + (N) *TVN_SIZE)
#define INDEX(V, N) ((V >> (TVR_BITS + (N) *TVN_BITS)) & TVN_MASK)



TimerManager::TimerManager() {
    m_timers.resize(TVR_SIZE + 4 * TVN_SIZE);
    m_checkTime = getCurrentMillisecs();
}

void TimerManager::addIntervalTimer(int interval, TimerCB cb, bool forever) {
    addTimer(interval, cb, forever);
}

void TimerManager::addMinuteTimer(int second, TimerCB cb, bool forever) {
    int seconds = second * COEF;
    unsigned long long now = getCurrentMillisecs();
    int interval = 0;
    int remain = now % (MINUTE * COEF);
    if (seconds > remain) {
        interval = seconds - remain;
    } else {
        interval = seconds + MINUTE * COEF - remain;
    }

    if (!forever) {
        addTimer(interval, cb, false);
        return;
    }

    addTimer(interval, std::bind(&TimerManager::minuteTimer, this, second, cb), false);
}

void TimerManager::addHourlyTimer(int minute, int second, TimerCB cb, bool forever) {
    int seconds = (minute * MINUTE + second) * COEF;
    unsigned long long now = getCurrentMillisecs();
    int interval = 0;
    int remain = now % (HOUR * COEF);
    if (seconds > remain) {
        interval = seconds - remain;
    } else {
        interval = seconds + HOUR * COEF - remain;
    }

    if (!forever) {
        addTimer(interval, cb, false);
        return;
    }

    addTimer(interval, std::bind(&TimerManager::hourlyTimer, this, minute, second, cb), false);
}

void TimerManager::addDailyTimer(int hour, int minute, int second, TimerCB cb, bool forever) {
    int seconds = (hour * HOUR +  minute * MINUTE + second) * COEF;
    unsigned long long now = getCurrentMillisecs();
    int interval = 0;
    int remain = now % (DAY * COEF) + LAG * COEF;
    if (seconds > remain) {
        interval = seconds - remain;
    } else {
        interval = seconds + DAY * COEF - remain;
    }

    addTimer(interval, std::bind(&TimerManager::dailyTimer, this, hour, minute, second, cb), false);
}

void TimerManager::tick() {
    std::thread([this] {
        while (true) {
            detectTimers();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }).detach();
}

void TimerManager::minuteTimer(int second, TimerCB cb) {
    if (cb) {
        cb();
    }

    int seconds = second * COEF;
    unsigned long long now = getCurrentMillisecs();
    int interval = 0;
    int remain = now % (MINUTE * COEF);
    if (seconds > remain) {
        interval = seconds - remain;
    } else {
        interval = seconds + MINUTE * COEF - remain;
    }

    addTimer(interval, std::bind(&TimerManager::minuteTimer, this, second, cb), false);
}

void TimerManager::hourlyTimer(int minute, int second, TimerCB cb) {
    if (cb) {
        cb();
    }

    int seconds = (minute * MINUTE + second) * COEF;
    unsigned long long now = getCurrentMillisecs();
    int interval = 0;
    int remain = now % (HOUR * COEF);
    if (seconds > remain) {
        interval = seconds - remain;
    } else {
        interval = seconds + HOUR * COEF - remain;
    }

    addTimer(interval, std::bind(&TimerManager::hourlyTimer, this, minute, second, cb), false);
}

void TimerManager::dailyTimer(int hour, int minute, int second, TimerCB cb) {
    if (cb) {
        cb();
    }

    int seconds = (hour * HOUR +  minute * MINUTE + second) * COEF;
    unsigned long long now = getCurrentMillisecs();
    int interval = 0;
    int remain = now % (DAY * COEF) + LAG * COEF;
    if (seconds > remain) {
        interval = seconds - remain;
    } else {
        interval = seconds + DAY * COEF - remain;
    }

    addTimer(interval, std::bind(&TimerManager::dailyTimer, this, hour, minute, second, cb), false);
}

unsigned long long TimerManager::getCurrentMillisecs() {
    timeval tv;    
    ::gettimeofday(&tv, 0);
    unsigned long long ret = tv.tv_sec;
    return ret * 1000 + tv.tv_usec / 1000;
}

void TimerManager::addTimer(int interval, TimerCB cb, bool forever) {
    Timer::ptr timer = std::make_shared<Timer>();
    timer->m_interval = interval;
    timer->m_cb = cb;
    timer->m_forever = forever;
    timer->m_expires = getCurrentMillisecs() + interval;

    addTimer(timer);
}

void TimerManager::addTimer(Timer::ptr timer) {
    unsigned long long expires = timer->m_expires;
    unsigned long long dur = expires - m_checkTime;

    if (dur < TVR_SIZE) {
        timer->m_index = expires & TVR_MASK;
    } else if (dur < (1 << (TVR_BITS + TVN_BITS))) {
        timer->m_index = OFFSET(0) + INDEX(expires, 0);
    } else if (dur < (1 << (TVR_BITS + 2 * TVN_BITS))) {
        timer->m_index = OFFSET(1) + INDEX(expires, 1);
    } else if (dur < (1 << (TVR_BITS + 3 * TVN_BITS))) {
        timer->m_index = OFFSET(2) + INDEX(expires, 2);
    } else if ((long long) dur < 0) {
        timer->m_index = m_checkTime & TVR_MASK;
    } else {
        if (dur > 0xffffffffUL) {
            dur = 0xffffffffUL;
            expires = dur + m_checkTime;
        }
        timer->m_index = OFFSET(3) + INDEX(expires, 3);
    }
 
    m_timers[timer->m_index].push_back(timer);
}

void TimerManager::detectTimers() {
    unsigned long long now = getCurrentMillisecs();
    while (m_checkTime <= now) {
        int index = m_checkTime & TVR_MASK;
        if (!index &&
            !cascade(OFFSET(0), INDEX(m_checkTime, 0)) &&
            !cascade(OFFSET(1), INDEX(m_checkTime, 1)) &&
            !cascade(OFFSET(2), INDEX(m_checkTime, 2))) {
            cascade(OFFSET(3), INDEX(m_checkTime, 3));
        }
        ++m_checkTime;

        std::list<Timer::ptr> tmp;
        tmp.splice(tmp.end(), m_timers[index]);
        for (auto it = tmp.begin(); it != tmp.end(); ++it) {
            Timer::ptr timer = *it;
            if (timer->m_forever) {
                timer->m_expires = timer->m_interval + now;
                addTimer(timer);
            }
            timer->m_cb();
        }
    }
}

int TimerManager::cascade(int offset, int index) {
    std::list<Timer::ptr> tmp;
    tmp.splice(tmp.end(), m_timers[offset + index]);
    for (auto it = tmp.begin(); it != tmp.end(); ++it) {
        addTimer(*it);
    }
    return index;
}