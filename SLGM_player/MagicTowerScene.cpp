#include "MagicTowerScene.h"
#include "MagicTowerObject.h"
#include "MagicTowerCharacter.h"
#include "MagicTowerPassiveObject.h"
#include "ResourceManager.h"
#include "script.h"
#include "CharacterPropertyExtension.h"
#include "QGraphicsView"

MagicTowerMap::MagicTowerMap(int _width, int _height)
{
    width = _width;
    height = _height;
}

bool MagicTowerMap::addLayer(QString name, int zValue)
{
    if(layers.find(name)!=layers.end()) return false;
    MagicTowerObject** newLayer = new MagicTowerObject*[width*height];
    layers.insert(name, newLayer);
    for(int i=0;i<width*height;i++)
    {
        newLayer[i] = NULL;
    }
    layerZOrders.insert(name, zValue);
    return true;
}

void MagicTowerMap::setActiveMap(bool isActived)
{
    QMapIterator<QString, MagicTowerObject**> i(layers);
    while (i.hasNext()) {
        i.next();
        for(int j=0;j<width*height;j++)
        {
            if(i.value()[j]!=NULL)
            {
                i.value()[j]->setVisible(isActived);
            }
        }
    }
}

MagicTowerObject* MagicTowerMap::getObjectAt(const QString& layer, const int gridX, const int gridY)
{
    Q_ASSERT(layers.find(layer)!=layers.end());
    Q_ASSERT(gridX>=0&&gridY>=0&&gridX<width&&gridY<height);
    return layers[layer][gridY*width+gridX];
}

MagicTowerObject* MagicTowerMap::setObjectAt(const QString& layer, const int gridX, const int gridY, MagicTowerObject* object, bool release)
{
    Q_ASSERT(layers.find(layer)!=layers.end());
    Q_ASSERT(gridX>=0&&gridY>=0&&gridX<width&&gridY<height);
    MagicTowerObject* oldObject = layers[layer][gridY*width+gridX];
    layers[layer][gridY*width+gridX] = object;
    if(object!=NULL)
    {
        object->gridX = gridX;
        object->gridY = gridY;
        object->layer = layer;
        object->setX(gridX*32);
        object->setY(gridY*32);
        object->setZValue(layerZOrders[layer]);
    }
    if(release)
    {
        if(oldObject!=NULL) delete oldObject;
        return NULL;
    }
    else
    {
        return oldObject;
    }
}

void MagicTowerMap::reset()
{
    QMapIterator<QString, MagicTowerObject**> i(layers);
    while (i.hasNext()) {
        i.next();
        for(int j=0;j<width*height;j++)
        {
            if(i.value()[j]!=NULL)
            {
                delete i.value()[j];
            }
        }
        delete i.value();
    }
}

MagicTowerMap::~MagicTowerMap()
{
    reset();
}

SLGMEditorScene::SLGMEditorScene(QObject* parent)
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

bool SLGMEditorScene::addMap(QString name, int width, int height)
{
    if(maps.find(name)!=maps.end()) return false;
    MagicTowerMap* map = new MagicTowerMap(width,height);
    maps.insert(name, map);
    return true;
}

MagicTowerMap* SLGMEditorScene::getMap(const QString& name)
{
    Q_ASSERT(maps.find(name)!=maps.end());
    return maps[name];
}

MagicTowerObject *SLGMEditorScene::setObjectAt(const QString& map, const QString& layer, int x, int y, MagicTowerObject* obj, bool release)
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

MagicTowerObject* SLGMEditorScene::setObjectAt(MagicTowerObject* oldObject, MagicTowerObject* newObject, bool release)
{
    return setObjectAt(oldObject->map, oldObject->layer,oldObject->getGridX(),oldObject->getGridY(),newObject,release);
}

MagicTowerObject* SLGMEditorScene::getObjectAt(const QString& map, const QString& layer, int x, int y)
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
    QMapIterator<QString, MagicTowerMap*> i(maps);
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
    Q_UNUSED(mouseEvent);
}

QList<QString> SLGMEditorScene::allMaps()
{
    return maps.keys();
}
