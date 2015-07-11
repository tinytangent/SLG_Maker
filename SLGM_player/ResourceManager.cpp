#include "ResourceManager.h"
#include <QSoundEffect>
#include <QThread>
#include <QDebug>

ResourceManager* ResourceManager::instance = NULL;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	QMapIterator<QString, QPixmap*> i(pixmapData);
    while (i.hasNext())
    {
        i.next();
        delete i.value();
    }
}

bool ResourceManager::addPixmap(const QString& alias, const QString& fileName)
{
	if(pixmapData.find(alias)!=pixmapData.end()) return false;
    QPixmap* pixmap = new QPixmap(fileName);
    if(pixmap->isNull())
    {
        delete pixmap;
        return false;
    }
	pixmapData.insert(alias, pixmap);
    return true;
}

const QPixmap& ResourceManager::getPixmap(const QString& alias) const
{
	if(pixmapData.find(alias)!=pixmapData.end())
		return *pixmapData[alias];
    else return nullPixmap;
}

bool ResourceManager::init()
{
    if(instance!=NULL) return false;
	instance = new ResourceManager();
    return true;
}

bool ResourceManager::release()
{
    if(instance==NULL) return false;
    delete instance;
    instance = NULL;
    return false;
}

ResourceManager* ResourceManager::getInstance()
{
    return instance;
}

bool ResourceManager::addAudio(const QString& alias, const QString& fileName)
{
	if(audioData.find(alias)!=audioData.end()) return false;
	QSoundEffect* audio = new QSoundEffect();
	audio->setSource(QUrl::fromLocalFile(fileName));
	audio->setVolume(1.0);
	audio->play();
	//TODO : cannot check whether audio load succeeded :(
	/*while(audio->status()==QSoundEffect::Loading)
	{
		QThread::msleep(50);
		qDebug() << "Sleep" << audio->status();
	}
	if(!audio->isLoaded())
	{
		delete audio;
		return false;
	}*/
	audioData.insert(alias, audio);
	return true;
}

QSoundEffect& ResourceManager::getAudio(const QString& alias)
{
	if(audioData.find(alias)!=audioData.end())
		return *audioData[alias];
	else return nullAudio;
}
