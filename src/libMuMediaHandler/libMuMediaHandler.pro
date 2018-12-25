#-------------------------------------------------
#
# Project created by QtCreator 2018-11-23T15:59:10
#
#-------------------------------------------------

QT       -= core gui

TARGET = MuMediaHandler
TEMPLATE = lib

DEFINES += MUMEDIAHANDLER_LIBRARY

include(../common.pri)

DESTDIR = $$PROJECT_LIBDIR

win32{
    DLLDESTDIR = $$PROJECT_BINDIR
    QMAKE_DISTCLEAN += $$PROJECT_BINDIR/MuMediaHandler.dll
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$PWD/src/MuMedia.cpp

HEADERS += \
    $$PWD/src/MuMedia.h \
    $$PWD/src/MuMedia_p.h \
    $$PWD/src/libMuMediaHandler_Global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#CONFIG += MuMediaHandler-buildlib

#include(libMuMediaHandler.pri)

#TARGET = $$LIBMUMEDIAHANDLER_NAME

#DESTDIR = $$PROJECT_LIBDIR

#win32{
#    DLLDESTDIR = $$PROJECT_BINDIR
#    QMAKE_DISTCLEAN += $$PROJECT_BINDIR/$${LIBMUMEDIAHANDLER_NAME}.dll
#}

#CONFIG += debug_and_release build_all

unix|win32: LIBS += -L$$PWD/lib/ -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale -ldsound -ldxguid

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
