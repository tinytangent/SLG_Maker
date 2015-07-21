#include "MagicTowerScene.h"
#include "SLGCGameUnit.h"
#include "MagicTowerCharacter.h"
#include "MagicTowerPassiveObject.h"
#include "SLGCResourceManager.h"
#include "script.h"
#include "CharacterPropertyExtension.h"
#include "QGraphicsView"

MagicTowerScene::MagicTowerScene(QObject* parent)
    :QGraphicsScene(parent)
{
    parentWidget = new QGraphicsView();
    parentWidget->setWindowTitle("魔塔");
    parentWidget->setScene(this);
    parentWidget->show();
    parentWidget->setSceneRect(QRectF(-5*32,0,18*32,13*32));
    parentWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    parentWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    parentWidget->setMinimumSize(18*32+2,
                                 13*32+2);
    activeCharacter = NULL;
    loadMap(this);
}

bool MagicTowerScene::addMap(QString name, int width, int height)
{
    if(maps.find(name)!=maps.end()) return false;
	SLGCGameMap* map = new SLGCGameMap(width,height);
    maps.insert(name, map);
    return true;
}

SLGCGameMap* MagicTowerScene::getMap(const QString& name)
{
    Q_ASSERT(maps.find(name)!=maps.end());
    return maps[name];
}

SLGCGameUnit *MagicTowerScene::setObjectAt(const QString& map, const QString& layer, int x, int y, SLGCGameUnit* obj, bool release)
{
    Q_ASSERT(x>=0&&y>=0&&x<getMap(map)->width&&y<getMap(map)->height);
    if(obj!=NULL)
    {
        obj->map = map;
        addItem(obj);
    }
    qDebug() << "ADDED";
    return getMap(map)->setObjectAt(layer,x,y,obj,release);
}

SLGCGameUnit* MagicTowerScene::setObjectAt(SLGCGameUnit* oldObject, SLGCGameUnit* newObject, bool release)
{
    return setObjectAt(oldObject->map, oldObject->layer,oldObject->getGridX(),oldObject->getGridY(),newObject,release);
}

SLGCGameUnit* MagicTowerScene::getObjectAt(const QString& map, const QString& layer, int x, int y)
{
    Q_ASSERT(x>=0&&y>=0&&x<getMap(map)->width&&y<getMap(map)->height);
    return getMap(map)->getObjectAt(layer,x,y);
}

bool MagicTowerScene::setActiveCharacter(MagicTowerCharacter* _activeCharacter)
{
    activeCharacter = _activeCharacter;
    setActiveMap(activeCharacter->getMap());
    _activeCharacter->setFocus();
    return true;
}

bool MagicTowerScene::setActiveMap(const QString& map)
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

MagicTowerCharacter* MagicTowerScene::getActiveCharacter()
{
    return activeCharacter;
}

void MagicTowerScene::reset()
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

QGraphicsView* MagicTowerScene::getParentWidget()
{
    return parentWidget;
}

void MagicTowerScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    Q_UNUSED(mouseEvent);
}

QList<QString> MagicTowerScene::allMaps()
{
    return maps.keys();
}
