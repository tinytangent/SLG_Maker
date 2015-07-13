#include "SLGMGameEditorWidget.h"
#include "MagicTowerScene.h"

SLGMGameEditorWidget::SLGMGameEditorWidget(QWidget *parent)
	: QWidget(parent),loader(this->gameScene)
{
	ui.setupUi(this);
	gameScene = new MagicTowerScene();
	ui.graphicsView->setScene(gameScene);
}

void SLGMGameEditorWidget::loadGame()
{

}

void SLGMGameEditorWidget::unloadGame()
{

}
