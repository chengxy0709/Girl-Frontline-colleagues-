#-------------------------------------------------
#
# Project created by QtCreator 2020-06-29T17:33:37
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GirlFrontline
TEMPLATE = app


SOURCES += main.cpp\
        gamestart.cpp \
    gamemap.cpp \
    figure.cpp \
    control.cpp \
    bullet.cpp \
    gameconsole.cpp \
    facility.cpp \
    effect.cpp \
    skill.cpp

HEADERS  += gamestart.h \
    mapinfo.h \
    gamemap.h \
    figure.h \
    figureinfo.h \
    control.h \
    bullet.h \
    gameconsole.h \
    missioninfo.h \
    facility.h \
    effect.h \
    skill.h

FORMS    += gamestart.ui

QMAKE_CXXFLAGS += -std=c++11
