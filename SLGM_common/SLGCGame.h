#ifndef _SLGC_GAME_H_
#define _SLGC_GAME_H_

#include <QMap>
#include <QObject>

class SLGCGameUnit;
class SLGCGameMap;

/**
 * @brief The SLGCGame class store complete information used to describe a game
 * It also handles save/load operations to read a game on disk or write a game in RAM to disk.
 * SLGCGame is top-level class of SLGM_common module, it is based on SLGM_logic, with additional graphical data.
 */
class SLGCGame : public QObject
{
	Q_OBJECT
public:
	QMap<QString, SLGCGameMap*> maps;
	/**
	 * @brief addMap 添加一张地图
	 * @param name 地图名称
	 * @param width 地图宽度
	 * @param height 地图高度
	 * @return 是否添加成功
	 */
	bool addMap(const QString &name, int width, int height);

	/**
	 * @brief getMap 根据名称获取地图
	 * @param name
	 * @return
	 */
	SLGCGameMap* getMap (const QString& name);
	QList<QString> allMaps();

	/**
	 * @brief addLayer像游戏场景添加一个图层
	 * @param map 要添加图层的地图名
	 * @param name 要添加图层的名称
	 * @return
	 */
	bool addLayer(const QString& map, const QString& name);

	//用于设置或者获取在某一处的对象
	SLGCGameUnit* setObjectAt(const QString& map, const QString& layer, int x, int y, SLGCGameUnit* obj, bool release = true);
	SLGCGameUnit* setObjectAt(SLGCGameUnit* oldObject, SLGCGameUnit* newObject, bool release = true);
	SLGCGameUnit* getObjectAt(const QString& map, const QString& layer, int x, int y);
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
signals:
	void unitAdded(SLGCGameUnit* unit);
};


#endif //_SLGC_GAME_H_
