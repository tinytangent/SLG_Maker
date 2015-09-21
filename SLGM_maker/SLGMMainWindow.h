#ifndef SLGMMAINWINDOW_H
#define SLGMMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include "ui_slgmmainwindow.h"

class SLGMEditorWidget;
class SLGMEditorScene;
class QHBoxLayout;
class SLGMObjectSelectorWidget;
class SLGMMapTreeEditor;

class SLGMMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit SLGMMainWindow(QWidget *parent = 0);
	SLGMEditorWidget* getEditorWidget();
	SLGMEditorScene* getEditorScene();

protected:
	Ui::MainWindow ui;
	SLGMEditorWidget* editorWidget;
	QFileDialog fileDialog;
	QHBoxLayout* mainLayout;
	SLGMObjectSelectorWidget* objectSelectorWidget;
	SLGMMapTreeEditor* widgetMapTreeEditor;
signals:

public slots:
	void onActionNew();
	void onActionOpen();
	void onActionClose();
	void onActionSave();
	void onActionSaveAs();
	void perfromMapClone(const QString& newMapName, const QString& oldMapName);
};

#endif // SLGMMAINWINDOW_H
