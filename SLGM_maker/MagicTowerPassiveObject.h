#ifndef MAGICTOWERPASSIVEOBJECT_H
#define MAGICTOWERPASSIVEOBJECT_H
#include "MagicTowerObject.h"

class MagicTowerPassiveObject;
class MagicTowerPassiveObjectEventHandler;

class MagicTowerPassiveObjectEventHandler : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief onAttemptMoveHandler适用于处理试图角色试图移动到物体的事件处理器
     * @param scene发生事件的的场景
     * @param obj 触发事件的对象
     * @return 是否允许角色移动
     */
    virtual bool onAttemptMoveHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj) = 0;

    /**
     * @brief onAttemptMoveHandler适用于处理试图角色已经移动到物体的事件处理器
     * @param scene发生事件的的场景
     * @param obj 触发事件的对象
     */
    virtual void onMoveToHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj) = 0;
};

typedef MagicTowerPassiveObjectEventHandler MTPOEHandler;

class MagicTowerPassiveObject : public MagicTowerObject
{
    Q_OBJECT
public:
    explicit MagicTowerPassiveObject(QGraphicsItem *parent = 0);
    //下面的两个函数本质上都是在调用handler中的对应函数，如果handler为NULL
    //onAttemptMoveHandler会返回NULL
    virtual bool onAttemptMoveHandler();
    virtual void onMoveToHandler();

    //事件处理器
    MTPOEHandler* handler;

    //自我复制函数
    virtual MagicTowerObject* clone();
signals:

public slots:

};

#endif // MAGICTOWERPASSIVEOBJECT_H
