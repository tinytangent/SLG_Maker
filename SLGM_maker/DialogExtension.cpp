#include "DialogExtension.h"
#include "MagicTowerCharacter.h"
#include <QPainter>
#include <QKeyEvent>

DialogExtension::DialogExtension(MagicTowerScene* scene) :
    MagicTowerExtension(scene)
    ,dialogBrush(QColor(0,0,0,192))
    ,dialogPen(QColor(64,64,64,192))
    ,dialogSize(100,100)
{
    dialogPen.setWidth(7);
    setDialogSize(QSize(100,100));
    setDialogSize(QSize(200,200));
    setZValue(1000);
    hideDialog();
}
void DialogExtension::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(dialogPen);
    painter->setBrush(dialogBrush);
    painter->drawRoundedRect(QRectF(0,0,dialogSize.width(),dialogSize.height()),30,30);
    qDebug("width: %d  ",dialogSize.width());
    qDebug("height: %d\n",dialogSize.height());
}

QRectF DialogExtension::boundingRect() const
{
    return QRectF(0,0,dialogSize.width(),dialogSize.height());
}
void DialogExtension::setDialogSize(const QSize& size)
{
    dialogSize.setWidth(size.width());
    dialogSize.setHeight(size.height());
    setX((18*32-size.width())/2-32*5);
    setY((13*32-size.height())/2);
    update();
}

const QSize& DialogExtension::getDialogSize()
{
    return dialogSize;
}

void DialogExtension::showDialog()
{
    setVisible(true);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void DialogExtension::hideDialog()
{
    setVisible(false);
    if(magicTowerScene->getActiveCharacter()!=NULL)
    magicTowerScene->getActiveCharacter()->setFocus();
}
