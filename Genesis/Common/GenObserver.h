#ifndef GENOBSERVER_H
#define GENOBSERVER_H

#include <vector>
#include <map>
#include <unordered_map>
#include <utility> // std::forword
#include <type_traits> // std::remove_pointer（C++11）


template <typename ... TPara>
class GenSlotBase
{
public:
    virtual ~GenSlotBase() = default;
    virtual void slotFunction(TPara ... para) = 0;
};

template <class TReceiver, typename ... TPara>
class GenSlot : public GenSlotBase<TPara...>
{
public:
    GenSlot(TReceiver * pObj, void (TReceiver::*func)(TPara... para)){
        m_recv = pObj;
        m_func = func;//使用 类外的 接收者类的 对象指针
    }
    virtual ~GenSlot() = default;
    void slotFunction(TPara ... para) override {
        if(m_recv && m_func) {
            (m_recv->*m_func)(std::forward<TPara>(para)...); // 成员对象指针调用类内的成员函数
        }
    }
private:
    TReceiver * m_recv; // 定义一个接收者的指针，在构造中初始化
    void (TReceiver::*m_func)(TPara... para);// 定义一个接收者类中的成员函数指针
};


template <typename ... TPara>
class GenSignal
{
private:
    std::vector<GenSlotBase<TPara...>*> vSignal;
public:
    template <class TReceiver>
    void addSlot(TReceiver * pObj, void (TReceiver::*func)(TPara... para)){
        vSignal.push_back(new GenSlot<TReceiver, TPara...>(pObj, func));
    }

    template <typename ... Args>
    void operator()(Args&& ... args) noexcept { // 声明不抛异常
        for(GenSlotBase<TPara...>* slot : vSignal){
            if(slot){
                // 将 args 完美转发给 slotFunction
                slot->slotFunction(std::forward<Args>(args)...);
            }
        }
    }

    template <class TReceiver>
    void removeSlot(TReceiver * pObj){
        for(auto it = vSignal.begin(); it != vSignal.end();){
            GenSlot<TReceiver, TPara...>* slot = dynamic_cast<GenSlot<TReceiver, TPara...>*>(*it);
            if(slot){
                delete slot;
                it = vSignal.erase(it);
            }else{
                ++it;
            }
        }
    }

    ~GenSignal() {
        for(GenSlotBase<TPara...>* slot : vSignal) {
            delete slot;
        }
        vSignal.clear();
    }
};

// #define GenConnect(sender, signal, receiver, method) (sender)->signal.addSlot(receiver, method)

/* 1. 用信号对象实例调用 addSlot（非静态成员函数必须这么写） */
/* 2. C++11 兼容：std::remove_pointer<...>::type（替代 C++14 的 remove_pointer_t） */
/* 3. typename 关键字：告诉编译器这是依赖类型（C++11 要求） */
#define GenConnect(sender, signal, receiver, method) \
    do { \
        ((sender)->signal).template addSlot< typename std::remove_pointer<decltype(receiver)>::type >(receiver, method); \
    } while(false)

#endif // GENOBSERVER_H
