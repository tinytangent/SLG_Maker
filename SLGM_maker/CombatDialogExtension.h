#ifndef COMBATDIALOGEXTENSION_H
#define COMBATDIALOGEXTENSION_H

#include "DialogExtension.h"

class MagicTowerPassiveObject;

class CombatDialogExtension : public DialogExtension
{
    Q_OBJECT
protected:
    //玩家操纵角色的指针
    MagicTowerCharacter* character;

    //怪物指针
    MagicTowerPassiveObject* monster;

    //攻击延时计时器
    QTimer* fightTimer;

    //下一个该进攻的对象，0为玩家，1为怪物
    int nextFighter;
public:
    //构造函数
    explicit CombatDialogExtension(MagicTowerScene* scene);

    //指定角色和怪物，并开启战斗
    virtual void beginFight(MagicTowerCharacter* _character, MagicTowerPassiveObject* _monster);

    //绘图更新方法
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    //析构函数，释放调用的资源
    ~CombatDialogExtension();
signals:

public slots:
    virtual void onFightTimer();

};

#endif // COMBATDIALOGEXTENSION_H
