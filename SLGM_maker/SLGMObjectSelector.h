#ifndef SLGMOBJECTSELECTOR_H
#define SLGMOBJECTSELECTOR_H

#include <QGraphicsObject>
class MagicTowerLoader;


class SLGMObjectSelector : public QGraphicsObject
{
public:
	MagicTowerLoader* loader;
	SLGMObjectSelector(MagicTowerLoader* _loader, QGraphicsItem * parent = 0);
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) Q_DECL_OVERRIDE;
	QRectF boundingRect() const Q_DECL_OVERRIDE;
};

#endif // SLGMOBJECTSELECTOR_H
