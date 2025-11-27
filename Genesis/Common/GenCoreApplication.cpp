#include "GenCoreApplication.h"
#include "GenObjectManager.h"
#include "GenModule.h"
#include "GenEventLoop.h"
#include "GenUtils.h"
#include "GenLogger.h"
#include "GenDateTime.h"
#include "../Api/IConfigManager.h"
#include "../Api/ILogger.h"
#include <thread>
#include <iostream>
#include <assert.h>

static GenCoreApplication * g_app = nullptr;


class GenWorker
{
public:
    std::function<void ()> m_proc;
    std::atomic<bool> m_finished; // 原子保护
    std::thread * m_thread;

    GenWorker(std::function<void ()> fn)
    {
        m_proc = fn;
        m_finished = false;
        m_thread = new std::thread([this]()
        {
            this->m_proc();
            this->m_finished = true;
        });
    }

    ~GenWorker()
    {
        if (m_thread){
            m_thread->join();
            delete m_thread; // 不delete有内存泄露风险
        }
    }
};

GenCoreApplication::GenCoreApplication(int & argc, char ** argv)
{
    if (g_app != nullptr) {
        throw std::runtime_error("Only one GenCoreApplication instance allowed!");
    }
    g_app = this;

    m_evtLoop = new GenEventLoop();
    m_typeCode = "Gen.CoreApplication";

    for(int i = 0; i < argc ;++i){
        m_arguments.push_back(std::string(argv[i]));
    }

    m_logMask = 0xFFFFFFFF; // 所以最高只有32种
}

GenCoreApplication::~GenCoreApplication()
{
    this->quit();
    delete m_evtLoop;

    auto it = m_workers.begin();
    for (; it != m_workers.end(); ++it){
        delete (*it);
    }
    m_workers.clear();

    if (g_app == this) {
        g_app = nullptr; // 防止悬空指针
    }
}

int GenCoreApplication::argc()
{
    return (int)m_arguments.size();
}

std::vector<std::string> GenCoreApplication::argv() const
{
    return m_arguments;
}

std::string GenCoreApplication::argv(int p)
{
    return m_arguments.at(p);
}

std::string GenCoreApplication::argv(const std::string &name)
{
    std::string k = name + "=";  // arg1=xxx arg2=xxx
    for (auto i = 0; i != m_arguments.size(); ++i){
        std::string argi = m_arguments.at(i);
        size_t p = argi.find(k);
        if (p != 0){
            continue;
        }
        std::string v = argi.substr(p + k.size());
        Gen::Str::trim(v);
        return v;
    }
    return std::string();
}

int GenCoreApplication::addModule(GenModule *module)
{
    std::string modName = module->getModuleName();
    if(m_modules.find(modName) == m_modules.end()){
        m_modules.insert(std::make_pair(modName, module));
        module->initialize(this->m_objectManager);
        return (int)m_modules.size();
    }
    // 日志需要在coreapp创建后定义
//    GEN_ERROR() << __FUNCTION__ << ", duplicate module:" << modName;
    std::cout << __FUNCTION__ << ", duplicate module:" << modName;
    return -1;
}

int GenCoreApplication::execute()
{
    m_evtLoop->addTimer(1000, true, [this](GenEvent *)
    {
        this->clearWorkers();
    });

    m_evtLoop->loop(-1, 20);
    return 0;
}

void GenCoreApplication::quit()
{
    m_evtLoop->quit();
}

GenObjectManager *GenCoreApplication::getObjectManager() const
{
    return m_objectManager;
}

std::string GenCoreApplication::applicationDirPath()
{
    assert(!m_arguments.empty());
    size_t p = std::string::npos;
    std::string t = this->m_arguments.at(0);
    p = t.find_last_of("/"); // unix
    if (p != std::string::npos){
        return t.substr(0, p);
    }
    p = t.find_last_of("\\"); // win
    if (p != std::string::npos){
        return t.substr(0, p);
    }
    return std::string();
}

std::string GenCoreApplication::applicaitonName()
{
    assert(!m_arguments.empty());

    size_t p = std::string::npos;
    std::string t = m_arguments.at(0);
    p = t.find_last_of("/");
    if (p != std::string::npos){
        t = t.substr(p + 1);
    }
    p = t.find_last_of("\\");
    if (p != std::string::npos){
        t = t.substr(p + 1);
    }
    p = t.find_last_of(".");
    if (p != std::string::npos){
        t = t.substr(0, p);
    }
    return t;
}

std::string GenCoreApplication::appDataPath()
{
    return "/data"; // 写死的，后续要修改
}

std::string GenCoreApplication::tempDataPath()
{
    return "/tmp"; // 写死的，后续要修改
}

int GenCoreApplication::setTimer(int interval, bool repeat,
                                 std::function<void (GenEvent *)> callback)
{
    return m_evtLoop->addTimer(interval, repeat, callback);
}

void GenCoreApplication::lock()
{
    m_lock.lock();
}

void GenCoreApplication::unlock()
{
    m_lock.unlock();
}

int GenCoreApplication::executeInWorker(const std::function<void ()>& fn)
{
    GenWorker * worker = new GenWorker(fn);
    m_workers.push_back(worker);
    return (int)m_workers.size();
}

GenCoreApplication * GenCoreApplication::GetApp()
{
    if (g_app == nullptr) {
        std::cout << "GenCoreApplication not initialized!";
    }
    return g_app;
}

void GenCoreApplication::logMessagePrint(const std::string& text, int level)
{
    assert(level >= 0 &&  level <= 31);
    if (m_logMask & (1 << level)){
        if (m_logHandlers[level]){
            m_logHandlers[level](text, level);
            return;
        }
        if (m_logHandlers[0]){
            m_logHandlers[0](text, level);
            return;
        }
        std::cout << "[" << GenDateTime::current().toString() << "] " << text << std::endl;
    }
}

void GenCoreApplication::sysMessagePrint(const std::string& text, const std::string& type, const std::string& color)
{
    static ILogger * p = nullptr;
    if (!p){
        p = this->getService<ILogger>(GENS_HTTPLOGGER);
    }
    if (p){
        p->addLogData(type, text, color);
    }
    //    std::cout << "logType=" << type << ", data=" << text << std::endl;
}

void GenCoreApplication::dutMessagePrint(const std::string& text, int dut, const std::string& color)
{
    static ILogger * p = nullptr;
    if (!p){
        p = this->getService<ILogger>(GENS_HTTPLOGGER);
    }
    if (p){
        p->addLogData(dut, text, color);
    }
    //    std::cout << "logDut=" << dut << ", data=" << text << std::endl;
}

void GenCoreApplication::setMessageFilter(int mask)
{
    m_logMask = mask;
}

void GenCoreApplication::setMessageHandler(int level, const std::function<void (const std::string &, int)> &handler)
{
    assert(level >= 0 && level <= 31);
    m_logHandlers[level] = handler;
}


void GenCoreApplication::clearWorkers()
{
    auto it = m_workers.begin();
    while (it != m_workers.end()){
        GenWorker * p = *it;
        if (p->m_finished){
            delete p;
            it = m_workers.erase(it);
        }else{
            ++it;
        }
    }
}

//void GenCoreApplication::messagePrint(int level, const std::string &text)
//{
//    std::cout << text << std::endl;
//}

IConfigManager * GetConfigManager()
{
    static IConfigManager * p = nullptr;
    if (!p){
        p = GenCoreApplication::GetApp()->getService<IConfigManager>(GENS_CFGMANAGER);
    }
    return p;
}
