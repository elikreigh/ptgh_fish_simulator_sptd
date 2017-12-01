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
    fish.cpp

HEADERS  += mainwindow.h \
    fish.h

FORMS    += mainwindow.ui

QT += uitools

