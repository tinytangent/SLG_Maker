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

SLGMEditorScene::SLGMEditorScene(QObject* parent)
    :QGraphicsScene(parent)
{
	/*parentWidget = new QGraphicsView();
    parentWidget->setWindowTitle("魔塔");
    parentWidget->setScene(this);
    parentWidget->show();
    parentWidget->setSceneRect(QRectF(-5*32,0,18*32,13*32));
    parentWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    parentWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	parentWidget->setMinimumSize((18+2)*32+2,
								 13*32+2);*/
	/*activeCharacter = NULL;
	SLGMObjectSelector* sel = new SLGMObjectSelector(NULL);

    loadMap(this);
	sel->setPos(QPointF(0,0));
	sel->setZValue(1e10);
		addItem(sel);*/
}

bool SLGMEditorScene::addMap(QString name, int width, int height)
{
    if(maps.find(name)!=maps.end()) return false;
	SLGCGameMap* map = new SLGCGameMap(width,height);
    maps.insert(name, map);
    return true;
}

SLGCGameMap* SLGMEditorScene::getMap(const QString& name)
{
    Q_ASSERT(maps.find(name)!=maps.end());
    return maps[name];
}

SLGCGameUnit *SLGMEditorScene::setObjectAt(const QString& map, const QString& layer, int x, int y, SLGCGameUnit* obj, bool release)
{
    Q_ASSERT(x>=0&&y>=0&&x<getMap(map)->width&&y<getMap(map)->height);
    if(obj!=NULL)
    {
        obj->map = map;
        addItem(obj);
    }
    return getMap(map)->setObjectAt(layer,x,y,obj,release);
}

SLGCGameUnit* SLGMEditorScene::setObjectAt(SLGCGameUnit* oldObject, SLGCGameUnit* newObject, bool release)
{
    return setObjectAt(oldObject->map, oldObject->layer,oldObject->getGridX(),oldObject->getGridY(),newObject,release);
}

SLGCGameUnit* SLGMEditorScene::getObjectAt(const QString& map, const QString& layer, int x, int y)
{
    Q_ASSERT(x>=0&&y>=0&&x<getMap(map)->width&&y<getMap(map)->height);
    return getMap(map)->getObjectAt(layer,x,y);
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
        this->maps[activeMap]->setActiveMap(false);
    }
    activeMap = map;
    this->maps[activeMap]->setActiveMap(true);
    return true;
}

MagicTowerCharacter* SLGMEditorScene::getActiveCharacter()
{
    return activeCharacter;
}

void SLGMEditorScene::reset()
{
    activeCharacter = NULL;
	QMapIterator<QString, SLGCGameMap*> i(maps);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }
    maps.clear();
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

QList<QString> SLGMEditorScene::allMaps()
{
    return maps.keys();
}
