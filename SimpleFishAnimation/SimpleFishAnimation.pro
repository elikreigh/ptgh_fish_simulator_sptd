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
    bubbles.cpp \
    floatingbubbles.cpp \
    fishfood.cpp \
    brain.cpp

HEADERS  += mainwindow.h \
    fish.h \
    bubbles.h \
    floatingbubbles.h \
    fishfood.h \
    brain.h

FORMS    += mainwindow.ui

QT += uitools

