#ifndef SLGMMAINWINDOW_H
#define SLGMMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "ui_slgmmainwindow.h"

class SLGMGameEditorWidget;

class SLGMMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit SLGMMainWindow(QWidget *parent = 0);

protected:
	Ui::MainWindow ui;
	SLGMGameEditorWidget* editorWidget;
signals:

public slots:
	void onActionNew();
};

#endif // SLGMMAINWINDOW_H
