#ifndef GENMESSAGELOGGER_H
#define GENMESSAGELOGGER_H


#include "GenGlobal.h"
#include "GenDebug.h"

class GenMessageLogger
{
public:
    GenMessageLogger();
    GenMessageLogger(int level);
    GenMessageLogger(const std::string& type, const std::string& color);
    GenMessageLogger(int dut, const std::string& color);
    GenMessageLogger(GenMessageHandler handler);
    ~GenMessageLogger();

    GenDebug debug();
    GenNoDebug noDebug();

protected:

protected:
    GenMessageHandler m_handler;
};

#endif // GENMESSAGELOGGER_H
