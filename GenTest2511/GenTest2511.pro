TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

include($$PWD/../../Genesis/Common/Common.pri)
include($$PWD/../../Genesis/Api/Api.pri)


LIBS += D:/YukiPrograms/boost_1_80_0/stage/lib/libboost_json-vc141-mt-gd-x64-1_80.lib
LIBS += D:/YukiPrograms/boost_1_80_0/stage/lib/libboost_container-vc141-mt-gd-x64-1_80.lib
LIBS += D:/YukiPrograms/boost_1_80_0/stage/lib/libboost_filesystem-vc141-mt-gd-x64-1_80.lib
LIBS += D:/YukiPrograms/boost_1_80_0/stage/lib/libboost_thread-vc141-mt-gd-x64-1_80.lib
LIBS += D:/YukiPrograms/boost_1_80_0/stage/lib/libboost_chrono-vc141-mt-gd-x64-1_80.lib

HEADERS += \
    TestObserver.h
