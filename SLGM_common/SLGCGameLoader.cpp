#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDebug>

#include "SLGCGame.h"
#include "SLGCGameBase.h"
#include "SLGCGameMap.h"
#include "SLGCGameLoader.h"
#include "SLGCGameUnit.h"

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
		return true;
	}
	else if(propertyType=="integer")
	{
		obj->addGameProperty(propertyName,propertyValue.toInt());
		return true;
	}
	return false;
}

bool SLGCGameLoader::loadMapFile(const QString& fileName)
{
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly))
	{
		return false;
	}
	QXmlStreamReader *xmlDocument = new QXmlStreamReader(&file);
	bool ret = parseMapFile(xmlDocument);
	file.close();
	delete xmlDocument;
	return ret;
}

bool SLGCGameLoader::writeMapFile(QXmlStreamWriter* writer)
{
	writer->setAutoFormatting(true);
	writer->writeStartDocument();
	writer->writeStartElement("map_data");
	QList<QString> maps = game->allMaps();
	for(int i=0;i<maps.size();i++)
	{
		writeMap(writer, maps[i]);
	}
	writer->writeEndElement();
	writer->writeEndDocument();
	return true;
}

bool SLGCGameLoader::writeProperties(QXmlStreamWriter* writer, SLGCGameBase* obj)
{
	QMap<QString, int> intProperties = obj->getAllIntGameProperties();
	QMap<QString, QString> stringProperties = obj->getAllStringGameProperties();
	foreach(const QString& propertyName, intProperties.keys())
	{
		writer->writeStartElement("property");
		writer->writeAttribute("name",propertyName);
		writer->writeAttribute("type","integer");
		writer->writeAttribute("value",QString("%1").arg(intProperties[propertyName]));
		writer->writeEndElement();
	}
	foreach(const QString& propertyName, stringProperties.keys())
	{
		writer->writeStartElement("property");
		writer->writeAttribute("name",propertyName);
		writer->writeAttribute("type","string");
		writer->writeAttribute("value",stringProperties[propertyName]);
		writer->writeEndElement();
	}
	return false;
}

bool SLGCGameLoader::writeMap(QXmlStreamWriter* writer, const QString& mapName)
{
	SLGCGameMap* map = game->getMap(mapName);
	writer->writeStartElement("map");
	writer->writeAttribute("name",mapName);
	writer->writeAttribute("width",QString("%1").arg(map->width));
	writer->writeAttribute("height",QString("%1").arg(map->height));
	writeProperties(writer,game->getMap(mapName));
	QList<QString> layers = game->allLayers(mapName);
	foreach (const QString& layerName, layers)
	{
		writer->writeStartElement("layer");
		writer->writeAttribute("name",layerName);
		writer->writeStartElement("layer_content");
		for(int i=0;i<map->height;i++)
		{
			for(int j=0;j<map->width;j++)
			{
				SLGCGameUnit* unit = game->getObjectAt(mapName,layerName,j,i);
				if(unit!=NULL) writer->writeCharacters(unit->presetName);
				else writer->writeCharacters("@null");
				if(i!=map->height-1||j!=map->width-1) writer->writeCharacters(",");
			}
		}
		writer->writeEndElement();
		writer->writeEndElement();
	}
	writer->writeEndElement();
	return true;
}

bool SLGCGameLoader::saveMapFile(const QString& fileName)
{
	QFile file(fileName);
	if(!file.open(QIODevice::WriteOnly))
	{
		return false;
	}
	QXmlStreamWriter writer(&file);
	bool ret = writeMapFile(&writer);
	file.close();
	return ret;
}

