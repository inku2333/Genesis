#ifndef GENDATETIME_H
#define GENDATETIME_H


#include <string>

class GenDateTime
{
protected:
    long long m_msec;

public:
    GenDateTime();

    GenDateTime(long long msec)
        : m_msec(msec)
    {

    }

    GenDateTime(const GenDateTime& dt)
        : m_msec(dt.m_msec)
    {

    }

    ~GenDateTime(){}

    GenDateTime& operator = (const GenDateTime& dt)
    {
        this->m_msec = dt.m_msec;
        return *this;
    }

    GenDateTime& operator += (const GenDateTime& dt)
    {
        this->m_msec += dt.m_msec;
        return *this;
    }

    GenDateTime& operator += (long long msec)
    {
        this->m_msec += msec;
        return *this;
    }

    GenDateTime& operator -= (const GenDateTime& dt)
    {
        this->m_msec -= dt.m_msec;
        return *this;
    }

    GenDateTime& operator -= (long long msec)
    {
        this->m_msec -= msec;
        return *this;
    }

    GenDateTime operator + (const GenDateTime& dt)
    {
        return GenDateTime(this->m_msec + dt.m_msec);
    }

    GenDateTime operator - (const GenDateTime& dt)
    {
        return GenDateTime(this->m_msec - dt.m_msec);
    }

    long long timeSpan(const GenDateTime& dt);

    static GenDateTime current();
    static long long currentMsecSinceEpoch();
    static long long currentSecSinceEpoch();
    static GenDateTime today();
    static GenDateTime fromSec(long long sec);

    static int setTimeZoneOffset(long long offset);

    std::string toString(const std::string& fmt);

    // format: yyyy-mm-dd HH:MM:SS.xxx
    std::string toString();
};

#endif // GENDATETIME_H
