#include "SGLCGameMap.h"
#include "SLGCGameUnit.h"

SLGCGameMap::SLGCGameMap(int _width, int _height)
{
	width = _width;
	height = _height;
}

bool SLGCGameMap::addLayer(QString name, int zValue)
{
	if(layers.find(name)!=layers.end()) return false;
	SLGCGameUnit** newLayer = new SLGCGameUnit*[width*height];
	layers.insert(name, newLayer);
	for(int i=0;i<width*height;i++)
	{
		newLayer[i] = NULL;
	}
	layerZOrders.insert(name, zValue);
	return true;
}

void SLGCGameMap::setActiveMap(bool isActived)
{
	QMapIterator<QString, SLGCGameUnit**> i(layers);
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

SLGCGameUnit* SLGCGameMap::getObjectAt(const QString& layer, const int gridX, const int gridY)
{
	Q_ASSERT(layers.find(layer)!=layers.end());
	Q_ASSERT(gridX>=0&&gridY>=0&&gridX<width&&gridY<height);
	return layers[layer][gridY*width+gridX];
}

SLGCGameUnit* SLGCGameMap::setObjectAt(const QString& layer, const int gridX, const int gridY, SLGCGameUnit* object, bool release)
{
	Q_ASSERT(layers.find(layer)!=layers.end());
	Q_ASSERT(gridX>=0&&gridY>=0&&gridX<width&&gridY<height);
	SLGCGameUnit* oldObject = layers[layer][gridY*width+gridX];
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

void SLGCGameMap::reset()
{
	QMapIterator<QString, SLGCGameUnit**> i(layers);
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

SLGCGameMap::~SLGCGameMap()
{
	reset();
}
