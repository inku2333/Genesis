#include <iostream>
#include "../../Genesis/Common/GenObserver.h"
#include "TestObserver.h"

int main(int argc, char *argv[])
{
    std::cout << "=== Test2511 ===" << std::endl;

    TReceiver1 * r1 = new TReceiver1;
    TReceiver2 * r2 = new TReceiver2;
    TReceiver3 * r3 = new TReceiver3;

    TSendObject * sd = new TSendObject;

    GenConnect(sd, signal1, r1, &TReceiver1::func);
    GenConnect(sd, signal1, r2, &TReceiver2::func);
    GenConnect(sd, signal2, r3, &TReceiver3::func);

    sd->testSendInt(222);
    sd->testSendString("test 333");


    return 0;
}
