QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

release: DESTDIR = ../shared/release
debug:   DESTDIR = ../shared/debug

TARGET = SLGM_common
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
	ResourceManager.h

SOURCES += \
	ResourceManager.cpp
