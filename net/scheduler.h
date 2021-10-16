#ifndef __NET_SCHEDULER_H__
#define __NET_SCHEDULER_H__

#include <chrono>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

const auto SYSTEM_TIME_ZERO = std::chrono::system_clock::time_point(std::chrono::milliseconds(0));

typedef std::function<void()> TaskFunc;

class Task {
public:
    typedef std::shared_ptr<Task> ptr;

    explicit Task(TaskFunc&& f)
        : m_func(std::forward<TaskFunc>(f)) {
    }

    Task(uint32_t ms, TaskFunc&& f)
        : m_expiration(std::chrono::system_clock::now() + std::chrono::milliseconds(ms))
        , m_func(std::forward<TaskFunc>(f)) {
    }

    virtual ~Task() = default;

    void operator()() {
        m_func();
    }

    bool hasExpired() const {
        if (m_expiration == SYSTEM_TIME_ZERO) {
            return false;
        }
        return m_expiration < std::chrono::system_clock::now();
    }

protected:
    std::chrono::system_clock::time_point m_expiration = SYSTEM_TIME_ZERO;

private:
    TaskFunc m_func;
};

Task::ptr createTask(TaskFunc&& f);
Task::ptr createTask(uint32_t expiration, TaskFunc&& f);

class Scheduler {
public:
    Scheduler(uint32_t num);

    void addTask(Task::ptr task);

private:
    std::vector<std::thread> m_works;

    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<Task::ptr> m_tasks;
};

#endif