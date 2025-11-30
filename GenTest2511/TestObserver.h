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
    void func(std::string para){
        std::cout << "TReceiver3::slotFunction(" << para.c_str() << ")" << std::endl;
    }
};

class TSendObject{
public:
    void testSendInt(int para){
        signal1(para);
    }
    void testSendString(std::string para){
        signal2(para);
    }
public:
    GenSignal<int> signal1;
    GenSignal<std::string> signal2;
};

//TReceiver1 * r1 = new TReceiver1;
//TReceiver2 * r2 = new TReceiver2;
//TReceiver3 * r3 = new TReceiver3;

//TSendObject * sd = new TSendObject;

//GenConnect(sd, signal1, r1, &TReceiver1::func);
//GenConnect(sd, signal1, r2, &TReceiver2::func);
//GenConnect(sd, signal2, r3, &TReceiver3::func);

//sd->testSendInt(222);
//sd->testSendString("test 333");


#endif // TESTOBSERVER_H
