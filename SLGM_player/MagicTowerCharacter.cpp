#include "MagicTowerCharacter.h"
#include "MagicTowerScene.h"
#include "MagicTowerPassiveObject.h"
#include "SLGCResourceManager.h"
#include "SaveLoadExtension.h"
#include "SGLCGameMap.h"
#include <QPropertyAnimation>
#include <QKeyEvent>
MagicTowerCharacter::MagicTowerCharacter()
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    connect(&moveAnimation,SIGNAL(finished()),this,SLOT(finishMove()));
}
void MagicTowerCharacter::keyPressEvent(QKeyEvent* event)
{
    MagicTowerScene* scene = dynamic_cast<MagicTowerScene*>(this->scene());
    if(event->isAutoRepeat()) return;
    switch(event->key())
    {
    case Qt::Key_Up:
        moveDirection = UP;
        break;
    case Qt::Key_Down:
        moveDirection = DOWN;
        break;
    case Qt::Key_Left:
        moveDirection = LEFT;
        break;
    case Qt::Key_Right:
        moveDirection = RIGHT;
        break;
    case Qt::Key_Escape:
        scene->getExtension<SaveLoadExtension>("saveLoad")->active();
        return;
    default:
        return;
    }
    //qDebug("Add Key");
    keyTable.append(moveDirection);
    Q_ASSERT(moveDirection>=0 && moveDirection<4);
    setPixmapFrameAnimation(directionAnimationData[moveDirection]);
    if(moveAnimation.state()==QPropertyAnimation::Stopped)
    {
        beginMove();
    }
}

void MagicTowerCharacter::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;
    Direction removedDirection;
    switch(event->key())
    {
    case Qt::Key_Up:
        removedDirection = UP;
        break;
    case Qt::Key_Down:
        removedDirection = DOWN;
        break;
    case Qt::Key_Left:
        removedDirection = LEFT;
        break;
    case Qt::Key_Right:
        removedDirection = RIGHT;
        break;
    default:
        return;
    }
    int keyCode = event->key();
    for(int i=0;i<keyTable.size();i++)
    {
        if(keyTable[i]==removedDirection)
        {
            //qDebug("Remove Key");
            keyTable.remove(i);
            i--;
        }
    }
    if(keyTable.empty())
    {
        if((keyCode==Qt::Key_Up||keyCode==Qt::Key_Down||keyCode==Qt::Key_Left||keyCode==Qt::Key_Right)&&moveDirection!=STOPPED)
        {
                Q_ASSERT(moveDirection>=0 && moveDirection<4);
            setPixmapFrameAnimation(directionSingleFrameData[moveDirection]);
            moveDirection = STOPPED;
        }
    }
    else
    {
        moveDirection = keyTable[keyTable.size()-1];
            Q_ASSERT(moveDirection>=0 && moveDirection<4);
        setPixmapFrameAnimation(directionAnimationData[moveDirection]);
    }

}

void MagicTowerCharacter::setCharacterAnimation(const QString& characterAnimationSheet)
{
    for(int i=0;i<4;i++)
    {
        this->directionAnimationData[i].clear();
        for(int j=0;j<4;j++)
        {
            AnimationFrame frame;
            frame.pixmapId = characterAnimationSheet;
			frame.pixmap = &SLGCResourceManager::getInstance()->getPixmap(characterAnimationSheet);
            frame.y = 32*i;
            frame.x = 32*j;
            directionAnimationData[i].append(frame);
        }
        directionSingleFrameData[i].clear();
        AnimationFrame frame;
        frame.pixmapId = characterAnimationSheet;
		frame.pixmap = &SLGCResourceManager::getInstance()->getPixmap(characterAnimationSheet);
        frame.y = 32*i;
        frame.x = 0;
        directionSingleFrameData[i].append(frame);

    }
    setPixmap(characterAnimationSheet);
}

void MagicTowerCharacter::beginMove()
{
    MagicTowerScene* scene = dynamic_cast<MagicTowerScene*>(this->scene());
	SLGCGameMap* map = scene->getMap(this->map);
    int targetX,targetY,originX = gridX,originY = gridY;
    switch(moveDirection)
    {
    case UP:
        targetX = gridX;
        targetY = gridY-1;
        break;
    case DOWN:
        targetX = gridX;
        targetY = gridY+1;
        break;
    case LEFT:
        targetX = gridX-1;
        targetY = gridY;
        break;
    case RIGHT:
        targetX = gridX+1;
        targetY = gridY;
        break;
    default:
        return;
    }
    if(!(targetX>=0&&targetX<=map->width-1&&targetY>=0&&targetY<=map->height-1))
    {
        return;
    }
    MagicTowerPassiveObject* originalObject = dynamic_cast<MagicTowerPassiveObject*>(map->getObjectAt("main",targetX,targetY));
    if(originalObject==NULL || originalObject->onAttemptMoveHandler())
    {
        map->setObjectAt(layer,gridX,gridY,NULL,false);
        map->setObjectAt(layer,targetX,targetY,this);
        moveAnimation.setTargetObject(this);
        moveAnimation.setPropertyName("pos");
        moveAnimation.setStartValue(QPointF(32*originX,32*originY));
        moveAnimation.setEndValue(QPointF(32*targetX,32*targetY));
        moveAnimation.setDuration(200);
        moveAnimation.start();
    }
}

void MagicTowerCharacter::finishMove()
{
    MagicTowerScene* scene = dynamic_cast<MagicTowerScene*>(this->scene());
	SLGCGameMap* map = scene->getMap(this->map);
    MagicTowerPassiveObject* originalObject = dynamic_cast<MagicTowerPassiveObject*>(map->getObjectAt("main",gridX,gridY));
    if(originalObject!=NULL) originalObject->onMoveToHandler();
    if(moveDirection!=STOPPED)
    {
        moveAnimation.stop();
        beginMove();
    }
    else
    {
        moveAnimation.stop();
        //setPixmapFrameAnimation(directionAnimationData[moveDirection]);
    }
}

void MagicTowerCharacter::focusOutEvent(QFocusEvent *event)
{
    moveDirection = STOPPED;
    keyTable.clear();
}

SLGCGameUnit* MagicTowerCharacter::clone()
{
    MagicTowerCharacter* ret = new MagicTowerCharacter();
    ret->gameProperties = this->gameProperties;
    ret->animationData = this->animationData;
    ret->currentFrame = this->currentFrame;
    for(int i=0;i<4;i++)
    {
        ret->directionAnimationData[i] = this->directionAnimationData[i];
        ret->directionSingleFrameData[i] = this->directionSingleFrameData[i];
    }
    ret->presetName = this->presetName;
    return ret;
}
