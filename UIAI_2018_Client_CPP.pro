QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = UIAI_2018_Client_CPP
CONFIG += console C++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    game.cpp \
    team.cpp \
    ball.cpp \
    pos.cpp \
    player.cpp \
    strategy.cpp \
    triple.cpp

win32{
    win32-g++{
         LIBS += -L"lib" -lWS2_32
       }
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    game.h \
    team.h \
    ball.h \
    pos.h \
    player.h \
    strategy.h \
    triple.h
