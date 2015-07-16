#ifndef SLGMGAMEEDITORWIDGET_H
#define SLGMGAMEEDITORWIDGET_H

#include <QWidget>
#include "ui_slgmgameeditorwidget.h"
#include "MagicTowerLoader.h"

class SLGMEditorScene;

class SLGMEditorWidget : public QWidget
{
	Q_OBJECT
protected:
	Ui::Form ui;
public:
	MagicTowerLoader* loader;
	SLGMEditorScene* gameScene;
	explicit SLGMEditorWidget(QWidget *parent = 0);
	void loadGame(const QString& filePath);
	void unloadGame();

signals:

public slots:
	void onMapSelectionChanged(const QString &newMap);
};

#endif // SLGMGAMEEDITORWIDGET_H
