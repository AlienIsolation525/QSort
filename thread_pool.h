#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <functional>
#include <memory>
#include <condition_variable>

class ThreadPool
{
public:
    ThreadPool() = default;
    void start();
    void stop();
    template<typename F, typename... Args> void push_task(F&& f, Args&&... args);
    void threadFunc();
private:
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_thread_queues;
    std::mutex m_locker;
    std::condition_variable m_event_holder;
    volatile bool m_work;
    int m_thread_count = 4;
};

template<typename F, typename... Args>
void ThreadPool::push_task(F&& f, Args&&... args){
    {
        std::lock_guard<std::mutex> l(m_locker);
        m_thread_queues.push(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    }
    m_event_holder.notify_one();
}