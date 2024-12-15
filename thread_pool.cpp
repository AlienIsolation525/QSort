#include "thread_pool.h"

void ThreadPool::start()
{
    m_work = true;
    for (int i = 0; i < m_thread_count; i++)
        m_threads.push_back(std::thread(&ThreadPool::threadFunc, this));
}


void ThreadPool::stop()
{
    m_work = false;
    m_event_holder.notify_all();
    for (auto& t : m_threads)
    {
        t.join();
    }
}

void ThreadPool::threadFunc()
{
    while (true){

        std::function<void()> task_to_do; {

            std::unique_lock<std::mutex> l(m_locker);
            if (m_thread_queues.empty() && !m_work)
            {
                return;
            }
            if (m_thread_queues.empty())
            {
                m_event_holder.wait(l, [&]() { return !m_thread_queues.empty() || !m_work; });
            }
            if (!m_thread_queues.empty())
            {
                task_to_do = m_thread_queues.front();
                m_thread_queues.pop();
            }
        }
        if (task_to_do)
        {
            task_to_do();
        }
    }
}