#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T16:00:09
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleFishAnimation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fish.cpp \
    bubbles.cpp \
    floatingbubbles.cpp \
    fishfood.cpp \
    brain.cpp \
    pillar.cpp \
    gamelogic.cpp \
    interferences.cpp

HEADERS  += mainwindow.h \
    fish.h \
    bubbles.h \
    floatingbubbles.h \
    fishfood.h \
    brain.h \
    pillar.h \
    gamelogic.h \
    interferences.h

FORMS    += mainwindow.ui

QT += uitools

RESOURCES += \
    sound.qrc \
    pictures.qrc

DISTFILES += \
    click.mp3 \
    shaker.mp3 \
    tankSound.mp3

