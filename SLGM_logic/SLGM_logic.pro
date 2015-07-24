QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

release: DESTDIR = ../shared/release
debug:   DESTDIR = ../shared/debug

TARGET = SLGM_logic
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../Lua_5.3.1

HEADERS += \
    Game.h \
    GameBase.h \
    GameboardSquare.h \
    GameEvent.h \
    GameLayerSquare.h \
    GameUnit.h \
    LuaTools.h

SOURCES += \
    Game.cpp \
    GameBase.cpp \
    GameBoardSquare.cpp \
    GameLayerSquare.cpp \
    GameUnit.cpp \
    LuaTools.cpp
