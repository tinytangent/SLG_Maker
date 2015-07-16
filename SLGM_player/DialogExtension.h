#ifndef DIALOGEXTENSION_H
#define DIALOGEXTENSION_H

#include "MagicTowerExtension.h"
#include <QSize>
#include <QRectF>
class DialogExtension : public MagicTowerExtension
{
    Q_OBJECT
protected:
    //对话框所默认使用的绘图样式和字体
    QBrush dialogBrush;
    QPen dialogPen;
    QFont textFont;

    //对话框的大小
    QSize dialogSize;
public:

    //构造函数
    explicit DialogExtension(SLGMEditorScene* scene);

    //绘图函数
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    //向场景报告自身大小和位置，与自动居中的功能有关。
    virtual QRectF boundingRect() const;

    //设置对话框大小
    virtual void setDialogSize(const QSize& size);

    //获取对话框大小
    virtual const QSize& getDialogSize();

    //显示对话框
    virtual void showDialog();

    //隐藏对话框
    virtual void hideDialog();
signals:

public slots:

};

#endif // DIALOGEXTENSION_H
