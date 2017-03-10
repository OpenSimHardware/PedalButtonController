#-------------------------------------------------
#
# Project created by QtCreator 2016-08-22T19:33:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSHStudio
TEMPLATE = app


SOURCES += main.cpp\
        oshstudio.cpp \
    hid.c

HEADERS  += oshstudio.h \
    hidapi.h

FORMS    += oshstudio.ui

RESOURCES += \
    oshstudio.qrc

win32 {

LIBS += -lhid -lsetupapi

}

DISTFILES +=

CONFIG += static
