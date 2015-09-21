#include "SLGCGame.h"
#include "SLGMMapTreeEditor.h"
#include "ui_SLGMMapTreeEditor.h"

SLGMMapTreeEditor::SLGMMapTreeEditor(SLGCGame *_game, QWidget *parent) :
	QWidget(parent),
	game(_game),
	ui(new Ui::SLGMMapTreeEditor)
{
	ui->setupUi(this);
}

SLGMMapTreeEditor::~SLGMMapTreeEditor()
{
	delete ui;
}

void SLGMMapTreeEditor::loadGameHierarchy()
{
	ui->treeWidget->clear();
	QStringList mapNames = game->allMaps();
	foreach(const QString& mapName, mapNames)
	{
		QTreeWidgetItem *mapItem = new QTreeWidgetItem();
		mapItem->setText(0, "Map: " + mapName);
		foreach(const QString& layerName, game->allLayers(mapName))
		{
			QTreeWidgetItem *layerItem = new QTreeWidgetItem(mapItem);
			layerItem->setText(0, "Layer: " + layerName);
		}

		ui->treeWidget->addTopLevelItem(mapItem);
	}
}
