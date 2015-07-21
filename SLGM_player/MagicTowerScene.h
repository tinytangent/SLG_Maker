#ifndef MAGICTOWERSCENE_H
#define MAGICTOWERSCENE_H

#include <QGraphicsScene>
#include <QMap>
#include <QGraphicsView>

class QString;
class SLGCGameUnit;
class MagicTowerCharacter;
class MagicTowerExtension;
class SLGCGameMap;
class CharacterPropertyExtension;

class MagicTowerScene : public QGraphicsScene
{
protected:

    /**
     * @brief parentWidget，MagicTowerScene创建时为自己创建的用于呈现自己的QGraphicsView对象
     */
    QGraphicsView* parentWidget;
    /**
     * @brief maps关联数组存储了魔塔中所有的地图（每一层是一张地图）
     */
	QMap<QString, SLGCGameMap*> maps;

    /**
     * @brief activeCharacter表示魔塔当前的“活动”（受操纵的）人物。
     */
    MagicTowerCharacter* activeCharacter;
    /**
     * @brief magicTowerExtensions存储了魔塔中所有的扩展对象。扩展对象的特点在于可以摆脱网格状结构存储的限制，
     * 获得键盘焦点，从而实现更多更复杂的功能。
     */
    QMap<QString, MagicTowerExtension*> magicTowerExtensions;

    /**
     * @brief activeMap记录了当前魔塔的活动地图（楼层），这在切换楼层时格外的有用。
     */
    QString activeMap;
public:

    /**
     * @brief 重置场景
     */
    void reset();

    /**
     * @brief 获取游戏主窗口
     * @return 指向游戏主窗口的指针
     */
    QGraphicsView* getParentWidget() ;

    /**
     * @brief addMap 添加一张地图
     * @param name 地图名称
     * @param width 地图宽度
     * @param height 地图高度
     * @return 是否添加成功
     */
    bool addMap(QString name, int width, int height);

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
    bool addLayer(QString map, QString name);

    //用于设置或者获取在某一处的对象
    SLGCGameUnit* setObjectAt(const QString& map, const QString& layer, int x, int y, SLGCGameUnit* obj, bool release = true);
    SLGCGameUnit* setObjectAt(SLGCGameUnit* oldObject, SLGCGameUnit* newObject, bool release = true);
    SLGCGameUnit* getObjectAt(const QString& map, const QString& layer, int x, int y);

    //设置当前的活动地图
    bool setActiveMap(const QString& map);

    template<class ExtType>
    bool addExtension(const QString& name)
    {
        if(magicTowerExtensions.find(name)!=magicTowerExtensions.end()) return false;
        magicTowerExtensions.insert(name, new ExtType(this));
        return true;
    }

    template<class ExtType>
    ExtType* getExtension(const QString& name)
    {
        return dynamic_cast<ExtType*>(magicTowerExtensions[name]);
    }

    /**
     * @brief setActiveCharacter设置一个“活动人物”，地图中的视角将根据活动人物进行调整。
     * 事实上，目前魔塔里只有一个人物，这一函数的意义在于初始化方便跟踪人物的位置。
     * @param activeCharacter魔塔中的活动人物
     * @return 设置活动人物是否成功
     */
    bool setActiveCharacter(MagicTowerCharacter* activeCharacter);

    /**
     * @brief getActiveCharacter获取当前的活动人物。
     * @return 当前的活动人物，可能为NULL。
     */
    MagicTowerCharacter* getActiveCharacter();
protected:
    //鼠标移动事件，用于覆盖基类避免焦点对象被意外改变
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
public:
	MagicTowerScene(QObject* parent = 0);
};

#endif // MAGICTOWERSCENE_H
