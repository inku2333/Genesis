#include "GenDateTime.h"
#include "GenUtils.h"
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include <assert.h>


long long g_tmOffset = 0;
long long g_tzOffset = 0;

GenDateTime::GenDateTime()
{
    std::chrono::system_clock clock;
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch()).count();
    m_msec = msec - g_tmOffset;
}

long long GenDateTime::timeSpan(const GenDateTime& dt)
{
    return abs(this->m_msec - dt.m_msec);
}

GenDateTime GenDateTime::current()
{
    std::chrono::system_clock clock;
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch()).count();
    return GenDateTime(msec - g_tmOffset);
}

long long GenDateTime::currentMsecSinceEpoch()
{
    std::chrono::system_clock clock;
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch()).count();
    return msec;
}

long long GenDateTime::currentSecSinceEpoch()
{
    std::chrono::system_clock clock;
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch()).count();
    return msec / 1000;
}

GenDateTime GenDateTime::today()
{
    std::chrono::system_clock clock;
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch()).count();
    time_t sec = (msec - g_tmOffset) / 1000;

    struct tm t;

#ifdef GEN_OS_WIN
    localtime_s(&t, &sec);
#else
    localtime_r(&sec, &t);
#endif

    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;

    sec = mktime(&t);
    msec = sec * 1000;
    return GenDateTime(msec);
}

GenDateTime GenDateTime::fromSec(long long sec)
{
    return GenDateTime(sec * 1000);
}

int GenDateTime::setTimeZoneOffset(long long offset)
{
    g_tzOffset = offset;
    return (int)g_tzOffset;
}

std::string GenDateTime::toString(const std::string& format)
{
    time_t sec = (m_msec - g_tzOffset) / 1000;
    struct tm t;
#ifdef GEN_OS_WIN
    localtime_s(&t, &sec);
#else
    localtime_r(&sec, &t);
#endif

    char buffer1[64] = {0};
    strftime(buffer1, sizeof(buffer1), format.c_str(), &t);
    return std::string(buffer1);
}

std::string GenDateTime::toString()
{
    std::string d1 = this->toString("%Y-%m-%d %H:%M:%S.");
    std::string d2 = "000" + std::to_string((int)(m_msec % 1000));
    return d1 + d2.substr(d2.length() - 3);
}

