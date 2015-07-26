#include "CharacterPropertyExtension.h"
#include "MagicTowerCharacter.h"
#include <QPainter>
#include <QApplication>
#include <QTextCodec>

CharacterPropertyExtension::CharacterPropertyExtension(MagicTowerScene * scene)
    :MagicTowerExtension(scene)
    ,textFont("黑体", 18)
{
    setPos(-32*5,0);
}

void CharacterPropertyExtension::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setFont(textFont);
    MagicTowerCharacter* currentCharacter = magicTowerScene->getActiveCharacter();
    if(currentCharacter == NULL) return;
    painter->drawText(QRect(0,0,200,100),QString("生命值:%1").arg(currentCharacter->getIntGameProperty("hitPoint")));
    painter->drawText(QRect(0,40,200,100),QString("攻击力:%1").arg(currentCharacter->getIntGameProperty("attack")));
    painter->drawText(QRect(0,80,200,100),QString("防御力:%1").arg(currentCharacter->getIntGameProperty("defense")));
    painter->drawText(QRect(0,120,200,100),QString("黄钥匙:%1").arg(currentCharacter->getIntGameProperty("yellowKey")));
    painter->drawText(QRect(0,160,200,100),QString("蓝钥匙:%1").arg(currentCharacter->getIntGameProperty("blueKey")));
    painter->drawText(QRect(0,200,200,100),QString("红钥匙:%1").arg(currentCharacter->getIntGameProperty("redKey")));
    painter->drawText(QRect(0,240,100,100),QString("金币:%1").arg(currentCharacter->getIntGameProperty("gold")));
    QString floor = currentCharacter->getMap();
    floor[floor.size()-1] = ' ';
    floor = floor.trimmed();
    painter->drawText(QRect(0,280,100,100),QString("楼层:%1").arg(floor.toInt()));
}

QRectF CharacterPropertyExtension::boundingRect() const
{
    return QRectF(0,0,32*5,32*13);
}
