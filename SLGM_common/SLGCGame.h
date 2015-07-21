#ifndef _SLGC_GAME_H_
#define _SLGC_GAME_H_

#include <QMap>
class SLGCGameUnit;
class SLGCGameUnit;

/**
 * @brief The SLGCGame class store complete information used to describe a game
 * It also handles save/load operations to read a game on disk or write a game in RAM to disk.
 * SLGCGame is top-level class of SLGM_common module, it is based on SLGM_logic, with additional graphical data.
 */
class SLGCGame
{
protected:
	//QMap<QString, SLGCGameObject*> objectPresets;
	QMap<QString, SLGCGameUnit*> unitPresets;
	bool loadResource(const QString& fileName);
	bool loadMap(const QString& fileName);
public:
	SLGCGame();
	~SLGCGame();
	bool loadProject(const QString& fileName);
	bool saveProject(const QString& fileName);
	bool exportGameExecutable(const QString& fileName);
	void reset();
	bool addObjectPreset();

	//The following methods provide supports to Game Unit
	bool addUnitPreset(const QString& presetName, SLGCGameUnit* unitPreset);
	bool removeUnitPreset(const QString& presetName);
	SLGCGameUnit* getUnitPreset(const QString& presetName);
	//SLGCGameUnit* setUnitPreset(const QString& presetName, SLGCGameUnit* unitPreset, bool release = true);

	//The following methods provide supports to Game Object
};


#endif //_SLGC_GAME_H_
