#ifndef GENEVENTLOOP_H
#define GENEVENTLOOP_H

#include "GenEvent.h"
#include <condition_variable>
#include <map>
#include <list>
#include <mutex>

class GenEventLoop
{
public:
    GenEventLoop();
    ~GenEventLoop() = default;
    //    GenEventLoop(const GenEventLoop& t) = default;
    //    GenEventLoop& operator = (const GenEventLoop& t) = default;

public:
    int addEventHandler(int type, GenEventHandler handler);
    int addEvent(int type, const boost::json::value& jsonData, GenEventData * eventData);
    int addEvent(int type, const boost::json::value& jsonData, GenEventData * eventData, GenEventHandler handler);
    int addTimer(int interval, bool repeat, GenEventHandler handler);
    void removeTimer(int timerId);

    void loop(int n, int timeout);
    void quit();

protected:
    void processEvents();
    void processTimers(); // 本质是添加event

protected:
    std::thread::id m_id;
    std::atomic_bool m_running; // 原子操作在无竞争时接近普通 bool 的性能（现代 CPU 通过缓存一致性协议优化）

    std::map<int, GenEventHandler> m_handlers;
    std::map<int, GenEventTimer> m_timers;
    int m_timerIdNum;

    std::list<GenEvent> m_events; // 后续可以改vector或deque
    std::mutex m_lock;
    std::condition_variable m_condi;
};

#endif // GENEVENTLOOP_H
