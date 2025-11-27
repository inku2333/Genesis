#ifndef GENEVENT_H
#define GENEVENT_H

#include <thread>
#include <functional>
#include <boost/json.hpp>

class GenEvent;
class GenEventData;

typedef std::function<void (GenEvent *)> GenEventHandler;

class GenEvent
{
public:
    GenEvent();
    ~GenEvent();
    GenEvent(int type,const boost::json::value& jsonData, GenEventData * eventData);
    GenEvent(int type, const boost::json::value& jsonData, GenEventData* eventData, GenEventHandler handler);
    GenEvent& operator = (const GenEvent& ev);
    GenEvent(const GenEvent& ev);

    bool isEmpty() const;
    void handle();

public:
    int m_type;
    boost::json::value m_jsonData; //适配非qt项目
    GenEventData * m_eventData;
    GenEventHandler m_eventHandler;
};

class GenEventData
{
public:
    GenEventData();
    // 遵循三法则
//    ~GenEventData() = default;
//    GenEventData(const GenEventData& t) = default;
//    GenEventData& operator = (const GenEventData& t) = default;
};

class GenEventTimer
{
public:
    GenEventTimer();
    GenEventTimer(const GenEventTimer& t);
    GenEventTimer(int timerId, int interval, bool repeat, GenEventHandler handler);
    ~GenEventTimer();

    GenEventTimer& operator = (const GenEventTimer& t);

public:
    int m_timerId;
    int m_interval;
    bool m_repeat;
    GenEventHandler m_handler;
    long long m_lastTriggered;
};

#endif // GENEVENT_H
