QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

release: DESTDIR = ../release
debug:   DESTDIR = ../debug

TARGET = SLGM_player
TEMPLATE = app
SOURCES += \
    main.cpp \
    MagicTowerScene.cpp \
    MagicTowerObject.cpp \
    MagicTowerCharacter.cpp \
    script.cpp \
    MagicTowerPassiveObject.cpp \
    MagicTowerExtension.cpp \
    CharacterPropertyExtension.cpp \
    DialogExtension.cpp \
    CombatDialogExtension.cpp \
    NPCDialogExtension.cpp \
    SaveLoadExtension.cpp \
    MagicTowerLoader.cpp \
    ResourceManager.cpp

HEADERS += \
    MagicTowerScene.h \
    MagicTowerObject.h \
    MagicTowerCharacter.h \
    script.h \
    MagicTowerPassiveObject.h \
    MagicTowerExtension.h \
    CharacterPropertyExtension.h \
    DialogExtension.h \
    CombatDialogExtension.h \
    NPCDialogExtension.h \
    SaveLoadExtension.h \
    MagicTowerLoader.h \
    ResourceManager.h
