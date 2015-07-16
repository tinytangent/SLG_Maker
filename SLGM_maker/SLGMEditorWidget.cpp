#include "SLGMEditorWidget.h"
#include "SLGMEditorScene.h"
#include "MagicTowerCharacter.h"

SLGMEditorWidget::SLGMEditorWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	gameScene = new SLGMEditorScene();
	loader = new MagicTowerLoader(this->gameScene);
	ui.graphicsView->setScene(gameScene);
	connect(ui.comboBoxMaps,SIGNAL(currentTextChanged(QString)),this,SLOT(onMapSelectionChanged(QString)));
}

void SLGMEditorWidget::loadGame(const QString &filePath)
{
	loader->loadGame(filePath);
	loader->loadMap(filePath + "/startup.mtmap.ini");
	MagicTowerCharacter* obj2= (MagicTowerCharacter*)loader->getPreset<MagicTowerCharacter>("warrior")->clone();
	this->gameScene->setObjectAt("1F","character",6,11,obj2);
	this->gameScene->setActiveCharacter(obj2);
	foreach(const QString& mapName, gameScene->allMaps())
	{
		ui.comboBoxMaps->insertItem(0,mapName);
	}
}

void SLGMEditorWidget::unloadGame()
{

}

void SLGMEditorWidget::onMapSelectionChanged(const QString& newMap)
{
	gameScene->setActiveMap(newMap);
}
