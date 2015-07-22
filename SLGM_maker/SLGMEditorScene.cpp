#include "SLGMEditorScene.h"
#include "SLGCGameUnit.h"
#include "MagicTowerCharacter.h"
#include "MagicTowerPassiveObject.h"
#include "SLGCResourceManager.h"
#include "script.h"
#include "CharacterPropertyExtension.h"
#include <QGraphicsView>
#include <SLGMObjectSelector.h>
#include "SLGMEditorWidget.h"
#include <QDebug>
#include "SLGCGame.h"

SLGMEditorScene::SLGMEditorScene(QObject* parent)
    :QGraphicsScene(parent)
{
	game = new SLGCGame();
	connect(game,SIGNAL(unitAdded(SLGCGameUnit*)),this,SLOT(onUnitAdded(SLGCGameUnit*)));
}

bool SLGMEditorScene::setActiveCharacter(MagicTowerCharacter* _activeCharacter)
{
    activeCharacter = _activeCharacter;
    setActiveMap(activeCharacter->getMap());
    _activeCharacter->setFocus();
    return true;
}

//TODO buggy on map =""
bool SLGMEditorScene::setActiveMap(const QString& map)
{
    if(map==activeMap) return true;
    if(activeMap!="")
    {
		this->game->maps[activeMap]->setActiveMap(false);
    }
    activeMap = map;
	this->game->maps[activeMap]->setActiveMap(true);
    return true;
}

MagicTowerCharacter* SLGMEditorScene::getActiveCharacter()
{
    return activeCharacter;
}

void SLGMEditorScene::reset()
{
    activeCharacter = NULL;
	QMapIterator<QString, SLGCGameMap*> i(game->maps);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }
	game->maps.clear();
    activeMap = "";
}

QGraphicsView* SLGMEditorScene::getParentWidget()
{
    return parentWidget;
}

void SLGMEditorScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	//TODO : This code is too ugly and requires refatcor.
	qDebug() << mouseEvent->scenePos().x() << mouseEvent->scenePos().y();
	int gridX = ((int)mouseEvent->scenePos().x()) / 32;
	int gridY = ((int)mouseEvent->scenePos().y()) / 32;
	if(currentCursorObject!="")
	{
		SLGMEditorWidget* w = dynamic_cast<SLGMEditorWidget*>(views().at(0)->parent());
		if(w!=NULL)
		{
			qDebug() << "AAA";
			setObjectAt(activeMap,"main",gridX,gridY,
					w->loader->getPreset<SLGCGameUnit>(currentCursorObject)->clone());
			//TODO: this is also weird due to current set object behaviour.
			//TODO: this implememntation is buggy.
			QString m = activeMap;
			setActiveMap("1F");
			setActiveMap("2F");
			setActiveMap(m);
		}
	}
	//Q_UNUSED(mouseEvent);
}

SLGCGameUnit* SLGMEditorScene::setObjectAt(const QString& map, const QString& layer, const int gridX, const int gridY, SLGCGameUnit* object, bool release)
{
	SLGCGameUnit* unit = game->setObjectAt(map, layer,gridX,gridY,object,release);
	/*if(object!=NULL)
	{
		addItem(object);
	}*/
}

void SLGMEditorScene::onUnitAdded(SLGCGameUnit* unit)
{
	addItem(unit);
}
