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
    hid.c \
    file_ops.cpp \
    board_types.cpp \
    oshaxiswca.cpp \
    get_put_config.cpp

HEADERS  += oshstudio.h \
    hidapi.h \
    oshaxiswca.h

FORMS    += oshstudio.ui \
    oshaxiswca.ui

RESOURCES += \
    oshstudio.qrc

win32 {

LIBS += -lhid -lsetupapi

}

DISTFILES +=

CONFIG += static
