QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

release: DESTDIR = ../shared/release
debug:   DESTDIR = ../shared/debug

TARGET = SLGM_common
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    SLGCResourceManager.h \
    SLGCGame.h \
    SLGCGameUnit.h \
    SLGCGameMap.h

SOURCES += \
    SLGCResourceManager.cpp \
    SGLCGame.cpp \
    SLGCGameUnit.cpp \
    SGLCGameMap.cpp
