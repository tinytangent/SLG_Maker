#ifndef MAGICTOWERCHARACTER_H
#define MAGICTOWERCHARACTER_H

#include "SLGCGameUnit.h"
#include <QPropertyAnimation>

enum Direction
{
    DOWN = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    STOPPED,
};
class MagicTowerCharacter : public SLGCGameUnit
{
    Q_OBJECT
protected:
    /**
     * @brief 角色的移动方向
     */
    Direction moveDirection;

    /**
     * @brief 用于移动的Qt动画对象
     */
    QPropertyAnimation moveAnimation;

    /**
     * @brief 预存的角色运动动画
     */
    QVector<AnimationFrame> directionAnimationData[5];

    /**
     * @brief 预存的角色静止图像
     */
    QVector<AnimationFrame> directionSingleFrameData[5];
    QVector<Direction> keyTable;
protected:

    /**
     * @brief keyPressEvent用于处理键盘按下的事件
     * @param event 事件对象
     */
    virtual void keyPressEvent(QKeyEvent* event);

    /**
     * @brief keyReleaseEvent用于处理键盘释放的事件
     * @param event 事件对象
     */
    virtual void keyReleaseEvent(QKeyEvent* event);

    /**
     * @brief focusOutEvent用于处理对象失去焦点的事件
     * @param event 事件对象
     */
    virtual void focusOutEvent(QFocusEvent * event);
public:
    /**
     * @brief 构造函数
     */
    explicit MagicTowerCharacter();

    /**
     * @brief 设置角色动画表，角色动画表应为长宽均为32*4的
     * @param 角色动画表
     */
    virtual void setCharacterAnimation(const QString& character);
	virtual SLGCGameUnit* clone();
public slots:
    /**
     * @brief beginMove用于处理移动开始的函数
     */
    virtual void beginMove();

    /**
     * @brief finishMove用于处理移动结束事件的函数
     */
    virtual void finishMove();
signals:
public slots:
};

#endif // MAGICTOWERCHARACTER_H
