#ifndef SLGMMAINWINDOW_H
#define SLGMMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
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
	QFileDialog fileDialog;
signals:

public slots:
	void onActionNew();
	void onActionOpen();
	void onActionClose();
	void onActionSave();
	void onActionSaveAs();
};

#endif // SLGMMAINWINDOW_H
