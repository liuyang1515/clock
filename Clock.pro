#-------------------------------------------------
#
# Project created by QtCreator 2014-06-28T21:00:26
#
#-------------------------------------------------

QT       += core gui multimedia sql network
CONFIG += c++11
LIBS += -lWs2_32

//LIBS+= Ws2_32.lib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Clock
TEMPLATE = app


SOURCES += main.cpp\
        Date.cpp \
        MyLabel.cpp \
        clock.cpp \
        memo.cpp \
        test.cpp \
        todolist/todolist.cpp

HEADERS  += clock.h \
    Date.h \
    MyLabel.h \
    connection.h \
    creation2.h \
    debug.h \
    memo.h \
    test.h \
    todolist/todolist.h \
    weather.h

FORMS    += clock.ui \
    memo.ui

RESOURCES += \
    images.qrc

RC_FILE = clock.rc
