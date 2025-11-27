#include "GenEvent.h"

GenEvent::GenEvent()
    :  m_type(0)
    , m_jsonData(0)
    , m_eventData(nullptr)
    , m_eventHandler(nullptr)
{

}

GenEvent::~GenEvent()
{

}

GenEvent::GenEvent(const GenEvent& ev)
    :  m_type(ev.m_type)
    , m_jsonData(ev.m_jsonData)
    , m_eventData(ev.m_eventData)
    , m_eventHandler(ev.m_eventHandler)
{

}

GenEvent::GenEvent(int type,const boost::json::value& jsonData, GenEventData * eventData)
    :  m_type(type)
    , m_jsonData(jsonData)
    , m_eventData(eventData)
    , m_eventHandler(nullptr)
{

}

GenEvent::GenEvent(int type, const boost::json::value& jsonData, GenEventData* eventData, GenEventHandler handler)
    :  m_type(type)
    , m_jsonData(jsonData)
    , m_eventData(eventData)
    , m_eventHandler(handler)
{

}

GenEvent& GenEvent::operator = (const GenEvent& ev)
{
    if(this != &ev){
        m_type = ev.m_type;
        m_jsonData = ev.m_jsonData;
        m_eventData = ev.m_eventData;
        m_eventHandler = ev.m_eventHandler;
    }
    return *this;
}

bool GenEvent::isEmpty() const
{
    return !m_eventHandler;
}

void GenEvent::handle()
{
    if(m_eventHandler){
        m_eventHandler(this);
    }
}

GenEventData::GenEventData()
{

}

GenEventTimer::GenEventTimer()
    : m_timerId(0)
    , m_interval(1)
    , m_repeat(0)
{
    m_lastTriggered = 0;
}


GenEventTimer::~GenEventTimer()
{

}

GenEventTimer::GenEventTimer(int timerId, int interval, bool repeat, GenEventHandler handler)
    : m_timerId(timerId)
    , m_interval(interval)
    , m_repeat(repeat)
{
    m_handler = handler;
    m_lastTriggered = 0;
}

GenEventTimer::GenEventTimer(const GenEventTimer& t)
    : m_timerId(t.m_timerId)
    , m_interval(t.m_interval)
    , m_repeat(t.m_repeat)
{
    m_handler = t.m_handler;
    m_lastTriggered = t.m_lastTriggered;
}

GenEventTimer& GenEventTimer::operator = (const GenEventTimer& t)
{
    if(this != &t){
        m_timerId = t.m_timerId;
        m_interval = t.m_interval;
        m_repeat = t.m_repeat;
        m_handler = t.m_handler;
        m_lastTriggered = t.m_lastTriggered;
    }
    return *this;
}
