#ifndef __LOGIC_TIMER_MANAGER_H__
#define __LOGIC_TIMER_MANAGER_H__

#include <list>
#include <memory>
#include <vector>
#include <functional>

typedef std::function<void(void)> TimerCB;

class TimerManager;

class Timer {
friend class TimerManager;
public:
    typedef std::shared_ptr<Timer> ptr;

private:
    int m_index;
    int m_interval;
    bool m_forever;
    unsigned long long m_expires;

    TimerCB m_cb;
};

class TimerManager {
public:
    typedef std::shared_ptr<TimerManager> ptr;

    TimerManager();

    void addIntervalTimer(int interval, TimerCB cb, bool forever = true);
    void addMinuteTimer(int second, TimerCB cb, bool forever = true);
    void addHourlyTimer(int minute, int second, TimerCB cb, bool forever = true);
    void addDailyTimer(int hour, int minute, int second, TimerCB cb, bool forever = true);

    void tick();

private:
    void minuteTimer(int second, TimerCB cb);
    void hourlyTimer(int minute, int second, TimerCB cb);
    void dailyTimer(int hour, int minute, int second, TimerCB cb);

    unsigned long long getCurrentMillisecs();

    void addTimer(Timer::ptr timer);
    void addTimer(int interval, TimerCB cb, bool forever = true);

    void detectTimers();

    int cascade(int offset, int index);

private:
    unsigned long long m_checkTime;
    std::vector<std::list<Timer::ptr>> m_timers;
};

#endif