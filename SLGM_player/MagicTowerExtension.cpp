#include "MagicTowerExtension.h"

MagicTowerExtension::MagicTowerExtension(SLGMEditorScene *_scene)
{
    this->magicTowerScene = _scene;
    magicTowerScene->addItem(this);
}

void MagicTowerExtension::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF MagicTowerExtension::boundingRect() const
{
    return QRectF(0,0,0,0);
}
