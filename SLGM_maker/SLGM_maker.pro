QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

release: DESTDIR = ../release
debug:   DESTDIR = ../debug

INCLUDEPATH += ../SLGM_common

LIBS += -L../shared/debug -lSLGM_common

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
    MagicTowerPassiveObject.cpp \
    NPCDialogExtension.cpp \
    SaveLoadExtension.cpp \
    script.cpp \
    SLGMObjectSelector.cpp \
    SLGMMainWindow.cpp \
    SLGMEditorScene.cpp \
    SLGMEditorWidget.cpp \
	SLGMObjectSelectorWidget.cpp

HEADERS += \
    MainWindow.h \
    CharacterPropertyExtension.h \
    CombatDialogExtension.h \
    DialogExtension.h \
    MagicTowerCharacter.h \
    MagicTowerExtension.h \
    MagicTowerLoader.h \
    MagicTowerPassiveObject.h \
    NPCDialogExtension.h \
    SaveLoadExtension.h \
    script.h \
    SLGMObjectSelector.h \
    SLGMMainWindow.h \
    SLGMEditorScene.h \
    SLGMEditorWidget.h \
	SLGMObjectSelectorWidget.h

FORMS += \
    slgmmainwindow.ui \
    slgmgameeditorwidget.ui \
    slgmobjectselectorwidget.ui
