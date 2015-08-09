#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

#include "SLGCGame.h"
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
				qDebug() << mapName << ".." << layerName;
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
