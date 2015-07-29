QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

release: DESTDIR = ../shared/release
debug:   DESTDIR = ../shared/debug

INCLUDEPATH += ../SLGM_logic

TARGET = SLGM_common
TEMPLATE = lib
CONFIG += staticlib
CONFIG += create_prl

HEADERS += \
    SLGCResourceManager.h \
    SLGCGame.h \
    SLGCGameUnit.h \
    SLGCGameMap.h \
    SLGCGameBase.h \
    SLGCGameLoader.h

SOURCES += \
    SLGCResourceManager.cpp \
    SGLCGame.cpp \
    SLGCGameUnit.cpp \
    SGLCGameMap.cpp \
    SLGCGameBase.cpp \
    SLGCGameLoader.cpp
