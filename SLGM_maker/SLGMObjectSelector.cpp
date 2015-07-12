#include <QPainter>
#include "SLGMObjectSelector.h"
SLGMObjectSelector::SLGMObjectSelector(MagicTowerLoader *_loader, QGraphicsItem *parent)
	:QGraphicsObject(parent),loader(_loader)
{

}

void SLGMObjectSelector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->drawText(0,20,"This is a selector");

}

QRectF SLGMObjectSelector::boundingRect() const
{
	return QRectF(0,0,1000,1000);
}
