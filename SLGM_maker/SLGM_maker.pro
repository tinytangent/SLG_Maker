QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

release: DESTDIR = ../release
debug:   DESTDIR = ../debug

TARGET = SLGM_maker
TEMPLATE = app
SOURCES += \
    main.cpp \
    CharacterPropertyExtension.cpp \
    CombatDialogExtension.cpp \
    DialogExtension.cpp \
    MagicTowerCharacter.cpp \
    MagicTowerExtension.cpp \
    MagicTowerLoader.cpp \
    MagicTowerObject.cpp \
    MagicTowerPassiveObject.cpp \
    NPCDialogExtension.cpp \
    ResourceManager.cpp \
    SaveLoadExtension.cpp \
    script.cpp \
    SLGMObjectSelector.cpp \
    SLGMMainWindow.cpp \
    SLGMEditorScene.cpp \
    SLGMEditorWidget.cpp

HEADERS += \
    MainWindow.h \
    CharacterPropertyExtension.h \
    CombatDialogExtension.h \
    DialogExtension.h \
    MagicTowerCharacter.h \
    MagicTowerExtension.h \
    MagicTowerLoader.h \
    MagicTowerObject.h \
    MagicTowerPassiveObject.h \
    NPCDialogExtension.h \
    ResourceManager.h \
    SaveLoadExtension.h \
    script.h \
    SLGMObjectSelector.h \
    SLGMMainWindow.h \
    SLGMEditorScene.h \
    SLGMEditorWidget.h

FORMS += \
    slgmmainwindow.ui \
    slgmgameeditorwidget.ui
