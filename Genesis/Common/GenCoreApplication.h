#ifndef GENCOREAPPLICATION_H
#define GENCOREAPPLICATION_H

// 未完成

#include "GenObject.h"
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <functional>
#include <mutex>

class GenObjectManager;
class GenModule;
class GenEventLoop;
class GenEvent;
class GenWorker;

class GenCoreApplication
        : public GenObject
{
public:
    GenCoreApplication(int & argc, char ** argv);
    virtual ~GenCoreApplication(); // 多态基类必须使用虚析构函数，这是C++资源管理的核心规则之一‌

    int argc();
    std::vector<std::string> argv() const;
    std::string argv(int p);
    std::string argv(const std::string& name);

    int addModule(GenModule * module);

    int execute();
    void quit();

    GenObjectManager * getObjectManager() const;

    std::string applicationDirPath();
    std::string applicaitonName();
    std::string appDataPath();
    std::string tempDataPath();

    int setTimer(int interval, bool repeat,std::function<void (GenEvent *)> callback);
    void lock();
    void unlock();
    int executeInWorker(const std::function<void ()>& fn);

    static GenCoreApplication * GetApp();

    void logMessagePrint(const std::string& text, int level);
    void sysMessagePrint(const std::string& text, const std::string& type, const std::string& color);
    void dutMessagePrint(const std::string& text, int dut, const std::string& color);

    void setMessageFilter(int mask);
    void setMessageHandler(int level, const std::function<void(const std::string&, int)>& handler);

protected:
    void clearWorkers();

protected:
    GenEventLoop * m_evtLoop;
    std::vector<std::string> m_arguments;

    std::map<std::string, GenModule *> m_modules;
    std::mutex m_lock;

    std::list<GenWorker *> m_workers;

    int m_logMask;
    std::function<void(const std::string&, int)> m_logHandlers[32];
};

namespace Gen
{

namespace App
{

template<typename T>
T * GetService(const std::string& serviceName)
{
    return GenCoreApplication::GetApp()->getService<T>(serviceName);
}

}

}

#endif // GENCOREAPPLICATION_H
