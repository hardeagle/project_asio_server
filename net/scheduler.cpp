#include "scheduler.h"

#include <log/glog.h>

Task::ptr createTask(TaskFunc&& f) {
	return std::make_shared<Task>(std::forward<TaskFunc>(f));
}

Task::ptr createTask(uint32_t expiration, TaskFunc&& f) {
	return std::make_shared<Task>(expiration, std::forward<TaskFunc>(f));
}

Scheduler::Scheduler(uint32_t num) {
    for (; num > 0; --num) {
        m_works.emplace_back([this] {
            while (true) {
                Task::ptr task;

                std::unique_lock<std::mutex> lock(m_mutex);
                m_cv.wait(lock, [this] {
                    return !m_tasks.empty();
                });

                if (m_tasks.empty()) {
                    continue;
                }

                task = m_tasks.front();
                m_tasks.pop();
                lock.unlock();

                (*task)();
            }
        });
    }
}

void Scheduler::addTask(Task::ptr task) {
    m_mutex.lock();
    m_tasks.emplace(task);
    m_mutex.unlock();

    m_cv.notify_one();
}