#ifndef _SLGC_GAME_BASE_H_
#define _SLGC_GAME_BASE_H_

#include "GameBase.h"
#include <QMap>

/**
 * @brief The SLGCGameBase class is a Qt-style wrapper class for GameBase class.
 * @see GameBase
 */
class QString;

class SLGCGameBase : protected GameBase
{
/*protected:
	GameBase stlGameBase;*/
public:
	SLGCGameBase();
	~SLGCGameBase();
	bool addGameProperty(const QString& name, const QString& value);
	bool addGameProperty(const QString& name, const int value);
	bool deleteGameProperty(const QString& name);
	bool setGameProperty(const QString& name, const QString& value);
	bool setGameProperty(const QString &name, const int value);
	bool getGameProperty(const QString& name, QString& value);
	bool getGameProperty(const QString& name, int& value);
	int getIntGameProperty(const QString& name);
	QString getStringGameProperty(const QString& name);
	QMap<QString, QString> getAllStringGameProperties();
	QMap<QString, int> getAllIntGameProperties();
};

#endif // SLGCGAMEBASE_H
