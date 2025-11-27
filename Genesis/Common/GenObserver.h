#ifndef GENOBSERVER_H
#define GENOBSERVER_H

#include <vector>
#include <map>
#include <unordered_map>

template <class TPara>
class GenSlotBase
{
public:
    virtual ~GenSlotBase() = default;
    virtual void slotFunction(TPara para) = 0;
};

template <class TReceiver, class TPara>
class GenSlot : public GenSlotBase<TPara>
{
public:
    GenSlot(TReceiver * pObj, void (TReceiver::*func)(TPara para)){
        m_recv = pObj;
        m_func = func;//使用类外的接收者类的对象指针
    }
    virtual ~GenSlot() = default;
    void slotFunction(TPara para) override {
        if(m_recv && m_func) (m_recv->*m_func)(para); // 成员对象指针调用类内的成员函数
    }
private:
    TReceiver * m_recv; // 定义一个接收者的指针，在构造中初始化
    void (TReceiver::*m_func)(TPara para);// 定义一个接收者类中的成员函数指针
};


template <class TPara>
class GenSignal
{
private:
    std::vector<GenSlotBase<TPara>*> signal;
};


#endif // GENOBSERVER_H
