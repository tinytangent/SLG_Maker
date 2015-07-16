QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = subdirs
#TARGET += SLGM_maker SLGM_player
#DEPENDPATH += . SLGM_maker SLGM_player
#INCLUDEPATH += . SLGM_maker SLGM_player
SUBDIRS = SLGM_maker SLGM_player
