#ifndef SLGMOBJECTSELECTORWIDGET_H
#define SLGMOBJECTSELECTORWIDGET_H

#include <QWidget>
#include "ui_slgmobjectselectorwidget.h"

class SLGMMainWindow;
class QStandardItemModel;

class SLGMObjectSelectorWidget : public QWidget
{
	Q_OBJECT
protected:
	SLGMMainWindow* mainWindow;
	Ui::ObjectSelector ui;
	QStandardItemModel* objectListModel;
public:
	explicit SLGMObjectSelectorWidget(SLGMMainWindow* _mainWindow);
	void updateObjectList();
signals:

public slots:
};

#endif // SLGMOBJECTSELECTORWIDGET_H
