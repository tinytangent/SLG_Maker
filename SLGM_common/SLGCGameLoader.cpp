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
			game->addMap(mapName, 13, 13);
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
	reader->readNext();
	forever
	{
		if(reader->isStartElement())
		{
			if(reader->name()=="layer")
			{
				parseMap(reader);
			}
		}
	}
}

bool SLGCGameLoader::parseLayer(QXmlStreamReader* reader, const QString& mapName)
{

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
