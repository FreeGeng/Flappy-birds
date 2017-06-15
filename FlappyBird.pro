#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T16:19:41
#
#-------------------------------------------------

QT       += core gui
QT      += widgets  multimedia

VERSION = 1.1.1

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DESTDIR = $$PWD
TARGET = FlappyBird

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bird.cpp \
    ground.cpp \
    pipe.cpp \
    scoreboard.cpp \
    fbnumlcd.cpp \
    redyboard.cpp

HEADERS  += mainwindow.h \
    bird.h \
    ground.h \
    pipe.h \
    scoreboard.h \
    fbnumlcd.h \
    redyboard.h

FORMS    +=

RESOURCES += \
    flappy.qrc
