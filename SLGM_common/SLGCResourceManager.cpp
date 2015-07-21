#include "SLGCResourceManager.h"
#include <QSoundEffect>
#include <QThread>
#include <QDebug>

SLGCResourceManager* SLGCResourceManager::instance = NULL;

SLGCResourceManager::SLGCResourceManager()
{
}

SLGCResourceManager::~SLGCResourceManager()
{
	QMapIterator<QString, QPixmap*> i(pixmapData);
    while (i.hasNext())
    {
        i.next();
        delete i.value();
    }
}

bool SLGCResourceManager::addPixmap(const QString& alias, const QString& fileName)
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

const QPixmap& SLGCResourceManager::getPixmap(const QString& alias) const
{
	if(pixmapData.find(alias)!=pixmapData.end())
		return *pixmapData[alias];
    else return nullPixmap;
}

bool SLGCResourceManager::init()
{
    if(instance!=NULL) return false;
	instance = new SLGCResourceManager();
    return true;
}

bool SLGCResourceManager::release()
{
    if(instance==NULL) return false;
    delete instance;
    instance = NULL;
    return false;
}

SLGCResourceManager* SLGCResourceManager::getInstance()
{
    return instance;
}

bool SLGCResourceManager::addAudio(const QString& alias, const QString& fileName)
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

QSoundEffect& SLGCResourceManager::getAudio(const QString& alias)
{
	if(audioData.find(alias)!=audioData.end())
		return *audioData[alias];
	else return nullAudio;
}
