#include <QPainter>
#include <QPixmap>
#include "MagicTowerObject.h"
#include "PixmapPool.h"
#include <QTimer>
#include <QDebug>

QTimer* MagicTowerObject::updateTimer = NULL;

MagicTowerObject::MagicTowerObject(QGraphicsItem* parent)
    :QGraphicsObject(parent)
{
    setVisible(false);
    initTimer();
}

void MagicTowerObject::initTimer()
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

MagicTowerObject::~MagicTowerObject()
{
}

void MagicTowerObject::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(animationData.size()==0) return;
    painter->drawPixmap(0,0,*animationData[currentFrame].pixmap,animationData[currentFrame].x,animationData[currentFrame].y,32,32);
}

QRectF MagicTowerObject::boundingRect() const
{
    return QRectF(0,0,32,32);
}

void MagicTowerObject::onFrameUpdateTimer()
{
    int frameCount = animationData.size();
    if(frameCount<=1) return;
    currentFrame++;
    if(currentFrame>=frameCount) currentFrame%=frameCount;
    update();
}

void MagicTowerObject::setPixmap(QString _pixmapId)
{
    animationData.clear();
    AnimationFrame frame;
    frame.x = frame.y = 0;
    frame.pixmapId = _pixmapId;
    frame.pixmap = &PixmapPool::getInstance()->getPixmap(_pixmapId);
    animationData.append(frame);
    currentFrame = 0;
    update();
}

void MagicTowerObject::setTwoFrameAnimation(QString _pixmapId)
{
    animationData.clear();
    AnimationFrame frame;
    frame.x = frame.y = 0;
    frame.pixmapId = _pixmapId;
    frame.pixmap = &PixmapPool::getInstance()->getPixmap(_pixmapId);
    animationData.append(frame);
    frame.x = 32;
    animationData.append(frame);
    currentFrame = 0;
    update();
}

void MagicTowerObject::setPixmapFrameAnimation(const QVector<AnimationFrame>& animation)
{
    animationData = animation;
    for(int i=0;i<animationData.size();i++)
    {
        animationData[i].pixmap=&PixmapPool::getInstance()->getPixmap(animationData[i].pixmapId);
    }
    currentFrame = 0;
}

bool MagicTowerObject::setGameProperty(const QString &name, int value)
{
    gameProperties[name] = value;
    return true;
}

int MagicTowerObject::getGameProperty(const QString& name)
{
    return gameProperties[name];
}

const QString& MagicTowerObject::getLayer()
{
    return layer;
}

const QString& MagicTowerObject::getMap()
{
    return map;
}

int MagicTowerObject::getGridX()
{
    return gridX;
}

int MagicTowerObject::getGridY()
{
    return gridY;
}

void MagicTowerObject::setPresetName(const QString &_presetName)
{
    presetName = _presetName;
}

MagicTowerObject* MagicTowerObject::clone()
{
    MagicTowerObject* ret = new MagicTowerObject();
    ret->gameProperties = this->gameProperties;
    ret->animationData = this->animationData;
    ret->currentFrame = this->currentFrame;
    ret->presetName = presetName;
    return ret;
}

const QMap<QString,int>& MagicTowerObject::getAllGameProperties()
{
    return gameProperties;
}
