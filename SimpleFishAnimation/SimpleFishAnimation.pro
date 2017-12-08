#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T16:00:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleFishAnimation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fish.cpp \
    brain.cpp \
    bubbles.cpp \
    fishfood.cpp \
    floatingbubbles.cpp \
    pillar.cpp

HEADERS  += mainwindow.h \
    fish.h \
    brain.h \
    bubbles.h \
    fishfood.h \
    floatingbubbles.h \
    pillar.h

FORMS    += mainwindow.ui

QT += uitools

