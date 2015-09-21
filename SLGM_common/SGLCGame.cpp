#include "SLGCGame.h"
#include "SLGCGameMap.h"
#include "SLGCGameUnit.h"
#include "SLGCGameLoader.h"
#include <QXmlStreamReader>
#include <QFile>

#include <QDebug>

SLGCGame::SLGCGame()
{
	loader = new SLGCGameLoader(this);
}

SLGCGame::~SLGCGame()
{

}


bool SLGCGame::addMap(const QString& name, int width, int height)
{
	if(maps.find(name)!=maps.end()) return false;
	SLGCGameMap* map = new SLGCGameMap(width,height);
	maps.insert(name, map);
	return true;
}

SLGCGameMap* SLGCGame::getMap(const QString& name)
{
	if(maps.find(name)==maps.end()) return NULL;
	return maps[name];
}

QList<QString> SLGCGame::allMaps() const
{
	return maps.keys();
}

SLGCGameUnit *SLGCGame::setObjectAt(const QString& map, const QString& layer, int x, int y, SLGCGameUnit* obj, bool release)
{
	if(x < 0 ||  y<0 || x>=getMap(map)->width ||y>=getMap(map)->height)
	{
		return NULL;
	}
	if(obj!=NULL)
	{
		obj->map = map;
		emit unitAdded(obj);
	}
	return getMap(map)->setObjectAt(layer,x,y,obj,release);
}

SLGCGameUnit* SLGCGame::setObjectAt(SLGCGameUnit* oldObject, SLGCGameUnit* newObject, bool release)
{
	return setObjectAt(oldObject->map, oldObject->layer,oldObject->getGridX(),oldObject->getGridY(),newObject,release);
}

SLGCGameUnit* SLGCGame::getObjectAt(const QString& map, const QString& layer, int x, int y)
{
	Q_ASSERT(x>=0&&y>=0&&x<getMap(map)->width&&y<getMap(map)->height);
	return getMap(map)->getObjectAt(layer,x,y);
}

bool SLGCGame::addUnitPreset(const QString& presetName, SLGCGameUnit* unitPreset)
{
	//TODO not implemented
	return false;
}

bool SLGCGame::removeUnitPreset(const QString& presetName)
{
	//TODO not implemented.
	return false;
}

SLGCGameUnit* SLGCGame::getUnitPreset(const QString& presetName)
{
	//TODO not implemented.
	return NULL;
}

bool SLGCGame::loadMap(const QString& fileName)
{
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "Failed to open file";
		return false;
	}

	loader->loadMapFile(fileName);
	QXmlStreamReader *xmlDocument = new QXmlStreamReader(&file);
	//qDebug() << "load Map called!";
	QXmlStreamReader::TokenType tt;
	while(!xmlDocument->atEnd())
	{
		if(xmlDocument->isStartElement())
		{
			//qDebug() << xmlDocument->name();
		}
		xmlDocument->readNext();
	}
	delete xmlDocument;
	file.close();
	return true;
}

bool SLGCGame::saveMap(const QString& fileName)
{
	return false;
}

bool SLGCGame::addLayer(const QString& map, const QString& name, int zOrder)
{
	//TODO : handle duplicate layer names.
	getMap(map)->addLayer(name, zOrder);
	return true;
}

QList<QString> SLGCGame::allLayers(const QString& mapName)
{
	return this->getMap(mapName)->layers.keys();
}
