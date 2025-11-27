#include "GenDebug.h"
#include "GenGlobal.h"
#include <iostream>
#include <assert.h>


GenDebug::GenDebug()
{
    m_stream = new GenDebug::Stream();
    m_handler = std::bind(&GenDebug::printData, this, std::placeholders::_1);
}

GenDebug::GenDebug(GenMessageHandler handler)
{
    m_stream = new GenDebug::Stream();
    m_handler = handler;
}

GenDebug::GenDebug(const GenDebug& d)
{
    m_stream = d.m_stream;
    m_handler = d.m_handler;
}

GenDebug::~GenDebug()
{
    --m_stream->refcnt;
    if (0 == m_stream->refcnt){
        m_handler(m_stream->ss.str());
        delete m_stream;
        m_stream = nullptr;
    }
}

GenDebug& GenDebug::operator = (const GenDebug& d)
{
    m_stream = d.m_stream;
    ++m_stream->refcnt;
    m_handler = d.m_handler;
    return *this;
}

GenDebug& GenDebug::format(const char * fmt, ...)
{
    char buffer[4 * 1024] = {0};
    va_list args;
    va_start(args, fmt);
    vsprintf_s(buffer, fmt, args);
    va_end(args);
    m_stream->ss << buffer;
    return *this;
}

GenDebug& GenDebug::operator << (const boost::json::object& v)
{
    this->m_stream->ss << boost::json::serialize(v);
    return *this;
}

GenDebug& GenDebug::operator << (const boost::json::array& v)
{
    this->m_stream->ss << boost::json::serialize(v);
    return *this;
}

void GenDebug::printData(const std::string &data)
{
    std::cout << data << std::endl;
}

GenNoDebug::GenNoDebug()
{

}

GenNoDebug::GenNoDebug(const GenNoDebug& d)
{
    GEN_UNUSED(d);
}

GenNoDebug::~GenNoDebug()
{

}
