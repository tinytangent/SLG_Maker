#include <QXmlStreamReader>

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
	forever
	{
		if(reader->isStartElement())
		{
			if(reader->name()=="map")
			{
				parseMap(reader);
			}
		}
	}
}

bool SLGCGameLoader::parseMap(QXmlStreamReader* reader)
{
	if((!reader->isStartElement())||(reader->name()!="map"))
	{
		return false;
	}
}

bool SLGCGameLoader::parseLayer(QXmlStreamReader* reader, const QString& mapName)
{

}
