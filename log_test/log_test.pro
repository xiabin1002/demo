TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += -I /home/mywork/01.ZGYZ/02.SP/KTX_SP/KTX_Trace_Client

unix:!macx: LIBS += -L$$PWD/../../mywork/01.ZGYZ/02.SP/build-KTX_SP-Debug/bin/ -lKTX_Trace_Clientd

INCLUDEPATH += $$PWD/../../mywork/01.ZGYZ/02.SP/build-KTX_SP-Debug/bin
DEPENDPATH += $$PWD/../../mywork/01.ZGYZ/02.SP/build-KTX_SP-Debug/bin
