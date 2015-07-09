QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

release: DESTDIR = ../release
debug:   DESTDIR = ../debug

TARGET = SLGM_maker
TEMPLATE = app
SOURCES += \
    main.cpp

HEADERS += \
    MainWindow.h \
