#include <QPainter>
#include <QPixmap>
#include "SLGCGameUnit.h"
#include "SLGCResourceManager.h"
#include <QTimer>
#include <QDebug>

QTimer* SLGCGameUnit::updateTimer = NULL;

SLGCGameUnit::SLGCGameUnit(QGraphicsItem* parent)
    :QGraphicsObject(parent)
{
    setVisible(false);
    initTimer();
}

void SLGCGameUnit::initTimer()
{
    if(updateTimer == NULL)
    {
        updateTimer = new QTimer();
        updateTimer->setInterval(250);
        updateTimer->setSingleShot(false);
        updateTimer->start();
    }
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(onFrameUpdateTimer()));
}

SLGCGameUnit::~SLGCGameUnit()
{
}

void SLGCGameUnit::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(animationData.size()==0) return;
    painter->drawPixmap(0,0,*animationData[currentFrame].pixmap,animationData[currentFrame].x,animationData[currentFrame].y,32,32);
}

QRectF SLGCGameUnit::boundingRect() const
{
    return QRectF(0,0,32,32);
}

void SLGCGameUnit::onFrameUpdateTimer()
{
    int frameCount = animationData.size();
    if(frameCount<=1) return;
    currentFrame++;
    if(currentFrame>=frameCount) currentFrame%=frameCount;
    update();
}

void SLGCGameUnit::setPixmap(QString _pixmapId)
{
    animationData.clear();
    AnimationFrame frame;
    frame.x = frame.y = 0;
    frame.pixmapId = _pixmapId;
	frame.pixmap = &SLGCResourceManager::getInstance()->getPixmap(_pixmapId);
    animationData.append(frame);
    currentFrame = 0;
    update();
}

void SLGCGameUnit::setTwoFrameAnimation(QString _pixmapId)
{
    animationData.clear();
    AnimationFrame frame;
    frame.x = frame.y = 0;
    frame.pixmapId = _pixmapId;
	frame.pixmap = &SLGCResourceManager::getInstance()->getPixmap(_pixmapId);
    animationData.append(frame);
    frame.x = 32;
    animationData.append(frame);
    currentFrame = 0;
    update();
}

void SLGCGameUnit::setPixmapFrameAnimation(const QVector<AnimationFrame>& animation)
{
    animationData = animation;
    for(int i=0;i<animationData.size();i++)
    {
		animationData[i].pixmap=&SLGCResourceManager::getInstance()->getPixmap(animationData[i].pixmapId);
    }
    currentFrame = 0;
}

const QString& SLGCGameUnit::getLayer()
{
    return layer;
}

const QString& SLGCGameUnit::getMap()
{
    return map;
}

int SLGCGameUnit::getGridX()
{
    return gridX;
}

int SLGCGameUnit::getGridY()
{
    return gridY;
}

void SLGCGameUnit::setPresetName(const QString &_presetName)
{
    presetName = _presetName;
}

SLGCGameUnit* SLGCGameUnit::clone()
{
	SLGCGameUnit* ret = new SLGCGameUnit();
    ret->gameProperties = this->gameProperties;
    ret->animationData = this->animationData;
    ret->currentFrame = this->currentFrame;
    ret->presetName = presetName;
    return ret;
}
