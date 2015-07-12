#ifndef MAGICTOWERSCENE_H
#define MAGICTOWERSCENE_H

#include <QGraphicsScene>
#include <QMap>
#include <QGraphicsView>

class QString;
class MagicTowerObject;
class MagicTowerCharacter;
class MagicTowerExtension;
class SLGMObjectSelector;
class CharacterPropertyExtension;

class MagicTowerMap
{
public:
    /**
     * @brief reset重置整张地图，已经添加到其中的所有对象。
     */
    void reset();

    /**
     * @brief layers地图中所存储的所有图层。
     */
    QMap<QString, MagicTowerObject**> layers;

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
    MagicTowerMap(int _width,int _height);

    /**
      * 析构函数，会释放内存。
      */
    ~MagicTowerMap();

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
    MagicTowerObject* getObjectAt(const QString& layer, const int gridX, const int gridY);

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
    MagicTowerObject* setObjectAt(const QString& layer, const int gridX, const int gridY, MagicTowerObject* object, bool release = true);
};

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
    QMap<QString, MagicTowerMap*> maps;

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
    MagicTowerMap* getMap (const QString& name);
    QList<QString> allMaps();

    /**
     * @brief addLayer像游戏场景添加一个图层
     * @param map 要添加图层的地图名
     * @param name 要添加图层的名称
     * @return
     */
    bool addLayer(QString map, QString name);

    //用于设置或者获取在某一处的对象
    MagicTowerObject* setObjectAt(const QString& map, const QString& layer, int x, int y, MagicTowerObject* obj, bool release = true);
    MagicTowerObject* setObjectAt(MagicTowerObject* oldObject, MagicTowerObject* newObject, bool release = true);
    MagicTowerObject* getObjectAt(const QString& map, const QString& layer, int x, int y);

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
