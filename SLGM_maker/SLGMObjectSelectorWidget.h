#ifndef SLGMOBJECTSELECTORWIDGET_H
#define SLGMOBJECTSELECTORWIDGET_H

#include <QWidget>
#include "ui_slgmobjectselectorwidget.h"

class SLGMObjectSelectorWidget : public QWidget
{
	Q_OBJECT
protected:
	Ui::ObjectSelector ui;
public:
	explicit SLGMObjectSelectorWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // SLGMOBJECTSELECTORWIDGET_H
