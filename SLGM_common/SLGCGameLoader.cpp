#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include <QDebug>

#include "SLGCGame.h"
#include "SLGCGameBase.h"
#include "SLGCGameMap.h"
#include "SLGCGameLoader.h"

SLGCGameLoader::SLGCGameLoader(SLGCGame *_game)
{
	game = _game;
}

bool SLGCGameLoader::parseMapFile(QXmlStreamReader* reader)
{
	forever
	{
		if(reader->isStartElement() && reader->name()=="map_data") break;
		if(reader->atEnd()) return false;
		reader->readNext();
	}
	while(!reader->atEnd())
	{
		if(reader->isStartElement() && reader->name()=="map")
		{
			QString mapName = reader->attributes().value("name").toString();
			parseMap(reader);
			qDebug() << mapName;
		}
		reader->readNext();
	}
	return true;
}

bool SLGCGameLoader::parseMap(QXmlStreamReader* reader)
{
	if((!reader->isStartElement())||(reader->name()!="map"))
	{
		return false;
	}
	QString mapName = reader->attributes().value("name").toString();
	game->addMap(mapName, 13, 13);
	while(!reader->atEnd())
	{
		if(reader->isStartElement() && reader->name()=="layer")
		{
			QString layerName = reader->attributes().value("name").toString();
			parseLayer(reader, mapName);
		}
		else if(reader->isStartElement() && reader->name()=="property")
		{
			parseProperty(reader, game->getMap(mapName));
		}
		if(reader->isEndElement() && reader->name()=="map") return true;
		reader->readNext();
	}
	return false;
}

bool SLGCGameLoader::parseLayer(QXmlStreamReader* reader, const QString& mapName)
{
	if((!reader->isStartElement())||(reader->name()!="layer"))
		return false;
	QString layerName = reader->attributes().value("name").toString();
	int zOrder = reader->attributes().value("z-order").toInt();
	game->addLayer(mapName, layerName, zOrder);
	while(!reader->atEnd())
	{
		if(reader->isStartElement() && reader->name()=="layer_content")
		{
			reader->readNext();
			QString origMapData = reader->text().toString();
			QStringList mapPartList = origMapData.split(",");
			qDebug()<<mapPartList.size();
			int mapPos = 0;
			SLGCGameMap* currentMap = game->getMap(mapName);
			for(int i=0;i<currentMap->width;i++)
			{
				for(int j=0;j<currentMap->height;j++)
				{
					//TODO:this is a temporary hack!
					if(i==0||i==12||j==0||j==12)
					{
						emit mapChanged(mapName, layerName, j, i, "null");
					}
					else
					{
						QString presetName =  mapPartList[mapPos].trimmed();
						qDebug() << "##" <<mapPos << presetName;
						emit mapChanged(mapName, layerName, j, i, presetName);
						mapPos++;
					}
				}
			}
		}
		else if(reader->isEndElement() && reader->name()=="layer") return true;
		reader->readNext();
	}
	return false;
}

bool SLGCGameLoader::loadMap(const QString& fileName)
{
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly))
	{
		return false;
	}
	QXmlStreamReader *xmlDocument = new QXmlStreamReader(&file);
	parseMapFile(xmlDocument);
	file.close();
	delete xmlDocument;
}

bool SLGCGameLoader::parseProperty(QXmlStreamReader* reader, SLGCGameBase* obj)
{
	if((!reader->isStartElement())||(reader->name()!="property"))
		return false;
	QString propertyName = reader->attributes().value("name").toString();
	QString propertyType = reader->attributes().value("type").toString();
	QString propertyValue = reader->attributes().value("value").toString();
	if(propertyType=="string")
	{
		obj->addGameProperty(propertyName,propertyValue);
	}
	else if(propertyType=="integer")
	{
		obj->addGameProperty(propertyName,propertyValue.toInt());
	}
}

