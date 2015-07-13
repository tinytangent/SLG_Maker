#include "SLGMEditorWidget.h"
#include "SLGMEditorScene.h"
#include "MagicTowerCharacter.h"

SLGMGameEditorWidget::SLGMGameEditorWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	gameScene = new MagicTowerScene();
	loader = new MagicTowerLoader(this->gameScene);
	ui.graphicsView->setScene(gameScene);
}

void SLGMGameEditorWidget::loadGame(const QString &filePath)
{
	loader->loadGame(filePath);
	loader->loadMap(filePath + "/startup.mtmap.ini");
	MagicTowerCharacter* obj2= (MagicTowerCharacter*)loader->getPreset<MagicTowerCharacter>("warrior")->clone();
	this->gameScene->setObjectAt("1F","character",6,11,obj2);
	this->gameScene->setActiveCharacter(obj2);
}

void SLGMGameEditorWidget::unloadGame()
{

}
