#include "GenEventLoop.h"
#include <QDate>

GenEventLoop::GenEventLoop()
{
    m_id = std::this_thread::get_id();
    m_timerIdNum = 0;
}

int GenEventLoop::addEventHandler(int type, GenEventHandler handler)
{
    assert(handler);
    int rc = -1;

    std::lock_guard<std::mutex> guard(m_lock);

    auto it = m_handlers.find(type);
    if (it == m_handlers.end()){
        m_handlers.insert(std::make_pair(type, handler));
        rc = 0;
    }

    return rc;
}

int GenEventLoop::addEvent(int type, const boost::json::value& jsonData, GenEventData *eventData)
{
    int rc = -1;
//    GenEvent evt(type, jsonData, eventData);

    {
        std::lock_guard<std::mutex> guard(m_lock);
        auto it = m_handlers.find(type);
        if (it != m_handlers.end()){
//            evt.m_eventHandler = it->second;
//            m_events.push_back(evt);
            m_events.emplace_back(type, jsonData, eventData, it->second);
            rc = 0;
        }
    }

    if(rc == 0){
        m_condi.notify_one(); // 不推荐在持有锁时通知
    }

    return rc;
}

int GenEventLoop::addEvent(int type, const boost::json::value& jsonData, GenEventData *eventData, GenEventHandler handler)
{
    assert(handler);

    {
        std::lock_guard<std::mutex> guard(m_lock);
        m_events.emplace_back(type, jsonData, eventData, handler);
    }
    m_condi.notify_one(); // 不推荐在持有锁时通知

    return 0;
}

int GenEventLoop::addTimer(int interval, bool repeat, GenEventHandler handler)
{
    assert(interval > 0 && handler);

    std::lock_guard<std::mutex> guard(m_lock);
    GenEventTimer timer(++m_timerIdNum, interval, repeat, handler);
    m_timers.insert(std::make_pair(timer.m_timerId, timer));

    return timer.m_timerId;
}

void GenEventLoop::removeTimer(int timerId)
{
    std::lock_guard<std::mutex> guard(m_lock);
    m_timers.erase(timerId);
}

void GenEventLoop::loop(int n, int timeout)
{
    m_running.store(true);
    while (m_running && n != 0){
        if (n > 0){
            n = n -1 ;
        }
        {
            std::unique_lock<std::mutex> lock(m_lock);
            m_condi.wait_for(lock,std::chrono::milliseconds(timeout),[this](){
                return !m_events.empty() || !m_running; // predicate：有evt时直接返回，不处理lock（仍然锁定）；谓语有两次检查，详见收藏夹
            });
        }
        this->processEvents();
        this->processTimers();
    }
    this->processEvents();

}

void GenEventLoop::quit()
{
    m_running.store(false);
    m_condi.notify_all(); // 唤醒所有等待线程
}

void GenEventLoop::processEvents()
{
    std::list<GenEvent> events;

    {
        std::lock_guard<std::mutex> lock(m_lock);
        events.swap(m_events);
    }

    auto it = events.begin();
    for (; it != events.end(); ++it){
        it->handle();
    }

}

void GenEventLoop::processTimers()
{
    std::lock_guard<std::mutex> lock(m_lock);

    auto it = m_timers.begin();
    while (it != m_timers.end()){

        long long current = QDateTime::currentMSecsSinceEpoch();
        long long duration = abs(current - it->second.m_lastTriggered);

        if (duration < it->second.m_interval){
            ++it;
            continue;
        }

        m_events.emplace_back(0, boost::json::value(), nullptr, it->second.m_handler);

        if (!it->second.m_repeat){
            it = m_timers.erase(it); // 直接删除当前到下一个，无需++it
        }else{
            it->second.m_lastTriggered = current;
            ++it;
        }
    }
}
