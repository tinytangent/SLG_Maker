#include "CombatDialogExtension.h"
#include "MagicTowerCharacter.h"
#include "MagicTowerPassiveObject.h"
#include <QMessageBox>
#include <QPainter>
#include <QTimer>
#include "CharacterPropertyExtension.h"
#include "SaveLoadExtension.h"

CombatDialogExtension::CombatDialogExtension(MagicTowerScene* scene) :
    DialogExtension(scene)
{
    fightTimer = new QTimer();
    fightTimer->setInterval(300);
    fightTimer->setSingleShot(false);
    connect(fightTimer,SIGNAL(timeout()),this,SLOT(onFightTimer()));
}

void CombatDialogExtension::beginFight(MagicTowerCharacter* _character, MagicTowerPassiveObject* _monster)
{
    character = _character;
    monster = _monster;
    nextFighter = 0;
    fightTimer->start();
    DialogExtension::showDialog();
}

CombatDialogExtension::~CombatDialogExtension()
{
    delete fightTimer;
}

void CombatDialogExtension::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    setDialogSize(QSize(400,200));
        DialogExtension::paint(painter, option, widget);
    QFont textFont("黑体", 18);
    painter->setFont(textFont);
    painter->setPen(QPen(Qt::white));
    painter->setBrush(QBrush(Qt::white));
    painter->drawText(QRect(0,40,200,100),QString("生命值:%1").arg(character->getIntGameProperty("hitPoint")));
    painter->drawText(QRect(0,80,200,100),QString("攻击力:%1").arg(character->getIntGameProperty("attack")));
    painter->drawText(QRect(0,120,200,100),QString("防御力:%1").arg(character->getIntGameProperty("defense")));
    painter->drawText(QRect(200,40,200,100),QString("怪物生命值:%1").arg(monster->getIntGameProperty("hitPoint")));
    painter->drawText(QRect(200,80,200,100),QString("怪物攻击力:%1").arg(monster->getIntGameProperty("attack")));
    painter->drawText(QRect(200,120,200,100),QString("怪物防御力:%1").arg(monster->getIntGameProperty("defense")));
}

void CombatDialogExtension::onFightTimer()
{
    if(nextFighter == 0)
    {
        int characterAttack = character->getIntGameProperty("attack")-monster->getIntGameProperty("defense");
        int monsterAttack = monster->getIntGameProperty("attack")-character->getIntGameProperty("defense");
        if(characterAttack<=0)
        {
            if(monsterAttack<=0)
            {
                characterAttack = 1;
            }
            else
            {
                characterAttack = 0;
            }
        }
        int monsterHp = monster->getIntGameProperty("hitPoint") - characterAttack;
        monster->setGameProperty("hitPoint", monsterHp);
        nextFighter = 1;
        if(monsterHp<=0)
        {
            int gold = character->getIntGameProperty("gold");
            gold += monster->getIntGameProperty("gold");
            character->setGameProperty("gold",gold);
            magicTowerScene->setObjectAt(monster->getMap(),monster->getLayer(),monster->getGridX(),monster->getGridY(),NULL);
            hideDialog();
            fightTimer->stop();
        }
    }
    else
    {
        int monsterAttack = monster->getIntGameProperty("attack")-character->getIntGameProperty("defense");
        if(monsterAttack <= 0)
        {
            monsterAttack = 0;
        }
        int characterHp = character->getIntGameProperty("hitPoint")-monsterAttack;
        character->setGameProperty("hitPoint", characterHp);
        if(characterHp<=0)
        {
            hideDialog();
            fightTimer->stop();
            QMessageBox::information(NULL,"游戏结束！","游戏结束！您可以加载之前的存档~");
            magicTowerScene->reset();
            magicTowerScene->getExtension<SaveLoadExtension>("saveLoad")->active();
        }
        nextFighter = 0;
    }
    update();
    magicTowerScene->getExtension<CharacterPropertyExtension>("characterProperty")->update();
}
