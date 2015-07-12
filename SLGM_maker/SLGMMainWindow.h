#ifndef SLGMMAINWINDOW_H
#define SLGMMAINWINDOW_H

#include <QMainWindow>
#include "ui_slgmmainwindow.h"

class SLGMMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit SLGMMainWindow(QWidget *parent = 0);

protected:
	Ui::MainWindow uiSetupHelper;
signals:

public slots:
};

#endif // SLGMMAINWINDOW_H
