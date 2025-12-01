#ifndef TESTOBSERVER_H
#define TESTOBSERVER_H

#include <iostream>
#include "../../Genesis/Common/GenObserver.h"

class TReceiver1{
public:
    void func(int para){
        std::cout << "TReceiver1::slotFunction(" << para << ")" << std::endl;
    }
};

class TReceiver2{
public:
    void func(int para){
        std::cout << "TReceiver2::slotFunction(" << para << ")" << std::endl;
    }
};

class TReceiver3{
public:
    void func(const std::string& para){
        std::cout << "TReceiver3::slotFunction(" << para.c_str() << ")" << std::endl;
    }
};

class TSendObject{
public:
    void testSendInt(int para){
        signal1(para);
    }
    void testSendString(const std::string& para){
        signal2(para);
    }
public:
    GenSignal<int> signal1;
    GenSignal<const std::string&> signal2;
};

// 多参数接收者示例
class MultiParamReceiver {
public:
    void onEvent(int id, const std::string& name, double value) {
        std::cout << "MultiParamReceiver::onEvent(" << id << ", " << name.c_str() << ", " << value << ")" << std::endl;
    }

    void onDataUpdate(const std::string& topic, int count) {
        std::cout << "MultiParamReceiver::onDataUpdate(" << topic.c_str() << ", " << count << ")" << std::endl;
    }
};

// 发送者类
class EventSender {
public:
    // 三参数信号
    GenSignal<int, const std::string&, double> multiParamSignal;

    // 双参数信号
    GenSignal<const std::string&, int> dataUpdateSignal;

    // 发送三参数事件
    void sendMultiParamEvent(int id, const std::string& name, double value) {
        multiParamSignal(id, name, value);
    }

    // 发送双参数事件
    void sendDataUpdate(const std::string& topic, int count) {
        dataUpdateSignal(topic, count);
    }
};

#endif // TESTOBSERVER_H


//std::cout << "=== Test2511 ===" << std::endl;

//// 原始测试
//TReceiver1 * r1 = new TReceiver1;
//TReceiver2 * r2 = new TReceiver2;
//TReceiver3 * r3 = new TReceiver3;

//TSendObject * sd = new TSendObject;

//(sd->signal1).addSlot<TReceiver1>(r1, &TReceiver1::func); // 不用宏

////    GenConnect(sd, signal1, r1, &TReceiver1::func);
//GenConnect(sd, signal1, r2, &TReceiver2::func);
//GenConnect(sd, signal2, r3, &TReceiver3::func);

//sd->testSendInt(222);
//sd->testSendString("updated test 333");

//// 多参数测试
//std::cout << "\n=== Multi Parameter Test ===" << std::endl;

//MultiParamReceiver* multiReceiver = new MultiParamReceiver;
//EventSender* sender = new EventSender;

//// 连接三参数信号
//GenConnect(sender, multiParamSignal, multiReceiver, &MultiParamReceiver::onEvent);

//// 连接双参数信号
//GenConnect(sender, dataUpdateSignal, multiReceiver, &MultiParamReceiver::onDataUpdate);

//// 发送多参数事件
//sender->sendMultiParamEvent(1, "ProductA", 99.99);
//sender->sendDataUpdate("Temperature", 25);

//// 清理内存
//delete r1;
//delete r2;
//delete r3;
//delete sd;
//delete multiReceiver;
//delete sender;
