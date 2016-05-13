TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    log4_demo.cpp \
    sigaction.cpp \
    fstream.cpp \
    read_file.cpp \
    sort.cpp \
    signal.c \
    sig_recv.c \
    sig_thread.c \
    iconv.cpp \
    sem.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS +=

OBJECTS_DIR = ./tmp
DESTDIR = ./Bin

unix:!macx: LIBS += -L$$PWD/ -llog4cplus
unix:!macx: LIBS += -lpthread
