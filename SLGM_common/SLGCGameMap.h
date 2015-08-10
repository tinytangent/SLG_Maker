#ifndef MAGICTOWERMAP_H
#define MAGICTOWERMAP_H

#include <QMap>

#include "SLGCGameBase.h"

class SLGCGameUnit;

class SLGCGameMap : public SLGCGameBase
{
public:
	/**
	 * @brief The reset method resets the whole map, removing all layers and units.
	 */
	void reset();

	/**
	 * @brief layers地图中所存储的所有图层。
	 */
	QMap<QString, SLGCGameUnit**> layers;

	/**
	 * @brief layerZOrders记录每一个图层的zOrder，即层叠显示顺序
	 */
	QMap<QString, int> layerZOrders;

	/**
	 * @brief 地图宽度
	 */
	int width;

	/**
	 * @brief 地图高度
	 */
	int height;

	/**
	 * @brief MagicTowerMap 构造函数，需要指定地图高度和宽度
	 * @param _width指定地图宽度
	 * @param _height指定地图高度
	 */
	SLGCGameMap(int _width,int _height);

	/**
	  * 析构函数，会释放内存。
	  */
	~SLGCGameMap();

	/**
	 * @brief addLayer 向地图之中添加图层
	 * @param name 地图的名称
	 * @param zValue 地图的zOrder，叠放次序
	 * @return 是否添加成功
	 */
	bool addLayer(QString name, int zValue);

	/**
	 * @brief setActiveMap设置当前图层的显示状态
	 * @param isActived当前图层是否显示
	 */
	void setActiveMap(bool isActived);

	/**
	 * @brief getObjectAt获取某一位置的对象
	 * @param layer图层名
	 * @param gridX横坐标
	 * @param gridY纵坐标
	 * @return 该位置的对象，可能为NULL
	 */
	SLGCGameUnit* getObjectAt(const QString& layer, const int gridX, const int gridY);

	QString backgroundMusic;

	/**
	 * @brief setObjectAt设置某一位置的对象
	 * @param layer图层名
	 * @param gridX横坐标
	 * @param gridY纵坐标
	 * @param object希望该位置被设置成的对象
	 * @param release是否delete该处原有的对象（安全的，如果原有为NULL，不delete）
	 * @return 如果原有的对象为NULL或release为true，则总是返回NULL，否则返回该处原有的对象（可以被复用）。
	 */
	SLGCGameUnit* setObjectAt(const QString& layer, const int gridX, const int gridY, SLGCGameUnit* object, bool release = true);
	//Extended properties:
};

#endif // MAGICTOWERMAP_H
