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
    get_put_config.cpp \
    oshpincombobox.cpp \
    worker.cpp \
    oshsingenc.cpp \
    osha2bw.cpp \
    oshbuttonw.cpp \
    draw_helps.cpp

HEADERS  += oshstudio.h \
    hidapi.h \
    oshaxiswca.h \
    oshpincombobox.h \
    hidapi.h \
    oshaxiswca.h \
    oshpincombobox.h \
    oshstudio.h \
    ../common_types/common_structs.h \
    worker.h \
    ../common_types/common_defines.h \
    oshsingenc.h \
    osha2bw.h \
    oshbuttonw.h

FORMS    += oshstudio.ui \
    oshaxiswca.ui \
    oshpincombobox.ui \
    oshsingenc.ui \
    osha2bw.ui \
    oshbuttonw.ui

RESOURCES += \
    oshstudio.qrc

win32 {

LIBS += -lhid -lsetupapi

}

DISTFILES +=

CONFIG += static
