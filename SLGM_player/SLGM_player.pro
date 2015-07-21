QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

release: DESTDIR = ../release
debug:   DESTDIR = ../debug

INCLUDEPATH += ../SLGM_common

LIBS += -L../shared/debug -lSLGM_common

TARGET = SLGM_player
TEMPLATE = app
SOURCES += \
    main.cpp \
    MagicTowerScene.cpp \
    MagicTowerCharacter.cpp \
    script.cpp \
    MagicTowerPassiveObject.cpp \
    MagicTowerExtension.cpp \
    CharacterPropertyExtension.cpp \
    DialogExtension.cpp \
    CombatDialogExtension.cpp \
    NPCDialogExtension.cpp \
    SaveLoadExtension.cpp \
	MagicTowerLoader.cpp

HEADERS += \
    MagicTowerScene.h \
    MagicTowerCharacter.h \
    script.h \
    MagicTowerPassiveObject.h \
    MagicTowerExtension.h \
    CharacterPropertyExtension.h \
    DialogExtension.h \
    CombatDialogExtension.h \
    NPCDialogExtension.h \
    SaveLoadExtension.h \
	MagicTowerLoader.h
