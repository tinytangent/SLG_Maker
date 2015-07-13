#ifndef SLGMGAMEEDITORWIDGET_H
#define SLGMGAMEEDITORWIDGET_H

#include <QWidget>
#include "ui_slgmgameeditorwidget.h"
#include "MagicTowerLoader.h"

class MagicTowerScene;

class SLGMGameEditorWidget : public QWidget
{
	Q_OBJECT
protected:
	Ui::Form ui;
	MagicTowerScene* gameScene;
	MagicTowerLoader* loader;
public:
	explicit SLGMGameEditorWidget(QWidget *parent = 0);

signals:

public slots:
	void loadGame(const QString& filePath);
	void unloadGame();
};

#endif // SLGMGAMEEDITORWIDGET_H
