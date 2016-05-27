TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    CKTXSerialPortCtrl.cpp \
#    sysdep1.c

#include(deployment.pri)
#qtcAddDeployment()

HEADERS += \
    CKTXSerialPortCtrl.h \
    sysdep.h

DESTDIR += ./bin
OBJECTS_DIR += ./tmp

