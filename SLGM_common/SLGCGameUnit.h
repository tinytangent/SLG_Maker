#ifndef MAGICTOWEROBJECT_H
#define MAGICTOWEROBJECT_H

#include <QGraphicsObject>
#include <QString>
#include <QVector>


class SLGMEditorScene;
class SLGCGameMap;

/**
 * @brief AnimationFrame类用来描述逐帧动画中的一帧。
 */
class AnimationFrame
{
public:
    /**
     * @brief 位图对应的PixmapPool中定义的alias
     */
    QString pixmapId;

    /**
     * @brief 该alias对应的pixmap对象指针，由系统自动生成
     */
    const QPixmap* pixmap;

    /**
     * @brief pixmap可以大于32*32，此参数表示选用区域在pixmap的横坐标
     */
    int x;

    /**
     * @brief pixmap可以大于32*32，此参数表示选用区域在pixmap的纵坐标
     */
    int y;
};

class SLGCGameUnit : public QGraphicsObject
{
	friend class SLGCGameMap;
    friend class SLGMEditorScene;
	friend class MagicTowerScene;

    Q_OBJECT
protected:
    //用于定位元素在魔塔中的位置，方便反向查找的信息
    /**
     * 网格位置横坐标
     */
    int gridX;

    /**
     * 网格位置纵坐标
     */
    int gridY;

    /**
     * 所在的地图名称
     */
    QString map;

    /**
     * 所在的图层名称
     */
    QString layer;

    //用于定义对象进行中状态的相关属性
    /**
     * 用于记录魔塔中对象属性的Key-Value对象
     */
    QMap<QString,int> gameProperties;
public:
    //用于定义对象帧动画定义的相关属性
    /**
     * @brief animationData向量列表的每一个元素定义了元素动画的一帧。
     */
    QVector<AnimationFrame> animationData;

    /**
     * @brief currentFrame用于存储动画当前播放到的帧。
     */
    int currentFrame;
public:
    //与存档功能有关的属性
    /**
     * @brief presetName表示对象从那个preset拷贝而来，对于存档功能有着重要意义。
     */
    QString presetName;
protected:
    //与帧动画计时器有关
    /**
     * @brief updateTimer所有MagicTowerObject是所有魔塔对象的共享4Hz计时器，用于实现逐帧动画。
     */
    static QTimer* updateTimer;

    /**
     * @brief initTimer用于帮助主第一个实例化的魔塔对象初始化计时器。
     */
    void initTimer();
public:

    /**
     * @brief 构造函数，初始化计时器并默认设置对象为隐藏。
     * @param parent父对象
     */
	SLGCGameUnit(QGraphicsItem* parent = 0);

    /**
      * 析构函数
      */
	~SLGCGameUnit();

    /**
     * @brief 实现基类的paint纯虚函数，用于完成对象的绘制任务。所有参数均未被实际使用。
     */
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    /**
     * @brief boundingRect实现基类的boundingRect纯虚函数，用于通知场景对象的可视区域大小（32*32px）
     * @return QRectF(0,0,32,32);
     */
    virtual QRectF boundingRect() const;

    /**
     * @brief setPixmap将魔塔对象的呈现方式设置为静态图片（只有一帧的动画
     * ）（从内置的位图缓存读取，要求图像大小不小于32*32，以（0,0）点为基准。
     * @param _pixmapId
     */
    virtual void setPixmap(QString _pixmapId);

    /**
     * @brief setTwoFrameAnimation将魔塔对象的呈现方式设置为两帧动画，
     * 从（0,0）开始向右连续读取两个32*32的块
     * @param _pixmapId
     */
    virtual void setTwoFrameAnimation(QString _pixmapId);

    /**
     * @brief setPixmapFrameAnimation设置魔塔对象的帧动画，该函数的自由度最大
     * 以AnimationFrame向量作为参数。
     * @param animation
     */
    virtual void setPixmapFrameAnimation(const QVector<AnimationFrame>& animation);

    /**
     * @brief setGameProperty用于设置游戏中一个魔塔网格对象的属性，如果该属性不存在则会被创建。
     * @param name 希望设置的属性的名字
     * @param value 希望属性被设置的值
     * @return 属性设置是否成功，目前总是返回true
     */
    virtual bool setGameProperty(const QString& name,int value);

    /**
     * @brief getGameProperty用于获取游戏中的一个魔塔网格对象属性。
     * @param name 希望获取的属性的名称。
     * @return 属性的值。注意如果属性没有被设置，会造成不可预期的结果。
     */
    virtual int getGameProperty(const QString& name);

    /**
     * @brief getAllGameProperties用于获取一个魔塔对象的全部属性
     * @return 全部属性的值。
     */
    virtual const QMap<QString,int>& getAllGameProperties();

    /**
     * @brief setPresetName设置游戏对象预设属性的名称
     * @param _presetName
     */
    virtual void setPresetName(const QString& _presetName);

    /**
     * @brief getLayer获取所在图层
     * @return
     */
    virtual const QString& getLayer();

    /**
     * @brief getMap获取所在地图
     * @return
     */
    virtual const QString& getMap();

    /**
     * @brief getGridX获取横坐标
     * @return
     */
    virtual int getGridX();

    /**
     * @brief getGridY获取纵坐标
     * @return
     */
    virtual int getGridY();

    /**
     * @brief 自我复制函数
     * @return
     */
	virtual SLGCGameUnit* clone();
public slots:

    /**
     * @brief 用于处理计时器更新信号的“槽”
     */
    virtual void onFrameUpdateTimer();
};

#endif // MAGICTOWEROBJECT_H
