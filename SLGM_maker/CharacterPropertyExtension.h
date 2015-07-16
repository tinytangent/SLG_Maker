#ifndef CHARACTERPROPERTYEXTENSION_H
#define CHARACTERPROPERTYEXTENSION_H

#include "MagicTowerExtension.h"

class CharacterPropertyExtension : public MagicTowerExtension
{
    Q_OBJECT
protected:
    //显示使用的字体
    QFont textFont;
public:

    //构造函数
    explicit CharacterPropertyExtension(MagicTowerScene* scene);

    //完成绘制
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    //声明显示区域
    virtual QRectF boundingRect() const;

signals:

public slots:

};

#endif // CHARACTERPROPERTYEXTENSION_H
