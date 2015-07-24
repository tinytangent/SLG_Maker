QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = subdirs
SUBDIRS += \
	SLGM_logic \
	SLGM_common \
	SLGM_maker \
	SLGM_player \
	Lua_5.3.1
