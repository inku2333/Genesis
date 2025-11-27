#include "GenMessageLogger.h"
#include "GenCoreApplication.h"
//#include "../Api/ILogger.h"
#include <iostream>


void LogMessagePrint(const std::string& text, int level)
{
    GenCoreApplication::GetApp()->logMessagePrint(text, level);
}

void SysMessagePrint(const std::string& text, const std::string& type, const std::string& color)
{
    GenCoreApplication::GetApp()->sysMessagePrint(text, type, color);
}

void DutMessagePrint(const std::string& text, int dut, const std::string& color)
{
    GenCoreApplication::GetApp()->dutMessagePrint(text, dut, color);
}


GenMessageLogger::GenMessageLogger()
{

}

GenMessageLogger::GenMessageLogger(int level)
{
    m_handler = std::bind(&LogMessagePrint, std::placeholders::_1, level);
}

GenMessageLogger::GenMessageLogger(const std::string& type, const std::string& color)
{
    m_handler = std::bind(&SysMessagePrint, std::placeholders::_1, type, color);
}

GenMessageLogger::GenMessageLogger(int dut, const std::string& color)
{
    m_handler = std::bind(&DutMessagePrint, std::placeholders::_1,  dut, color);
}

GenMessageLogger::GenMessageLogger(GenMessageHandler handler)
{
    m_handler = handler;
}

GenMessageLogger::~GenMessageLogger()
{

}

GenDebug GenMessageLogger::debug()
{
    if (m_handler){
        return GenDebug(m_handler);
    }
    return GenDebug();
}

GenNoDebug GenMessageLogger::noDebug()
{
    return GenNoDebug();
}

