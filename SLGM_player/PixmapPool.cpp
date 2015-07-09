#include "PixmapPool.h"

#include <QMap>
#include <QPixmap>

PixmapPool* PixmapPool::instance = NULL;

PixmapPool::PixmapPool()
{
}

PixmapPool::~PixmapPool()
{
    QMapIterator<QString, QPixmap*> i(data);
    while (i.hasNext())
    {
        i.next();
        delete i.value();
    }
}

bool PixmapPool::addPixmap(const QString& alias, const QString& fileName)
{
    if(data.find(alias)!=data.end()) return false;
    QPixmap* pixmap = new QPixmap(fileName);
    if(pixmap->isNull())
    {
        delete pixmap;
        return false;
    }
    data.insert(alias, pixmap);
    return true;
}

const QPixmap& PixmapPool::getPixmap(const QString& alias) const
{
    if(data.find(alias)!=data.end())
        return *data[alias];
    else return nullPixmap;
}

bool PixmapPool::init()
{
    if(instance!=NULL) return false;
    instance = new PixmapPool();
    return true;
}

bool PixmapPool::release()
{
    if(instance==NULL) return false;
    delete instance;
    instance = NULL;
    return false;
}

PixmapPool* PixmapPool::getInstance()
{
    return instance;
}
