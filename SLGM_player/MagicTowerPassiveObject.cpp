#include "MagicTowerPassiveObject.h"
#include "MagicTowerScene.h"

MagicTowerPassiveObject::MagicTowerPassiveObject(QGraphicsItem* parent)
    :SLGCGameUnit(parent)
{
    handler = NULL;
}

bool MagicTowerPassiveObject::onAttemptMoveHandler()
{
    MagicTowerScene* scene = dynamic_cast<MagicTowerScene*>(this->scene());
    if(handler!=NULL)
    {
        return handler->onAttemptMoveHandler(scene, this);
    }
    else
    {
        return false;
    }
}

SLGCGameUnit* MagicTowerPassiveObject::clone()
{
    MagicTowerPassiveObject* ret = new MagicTowerPassiveObject();
    ret->gameProperties = this->gameProperties;
    ret->animationData = this->animationData;
    ret->currentFrame = this->currentFrame;
    ret->handler = this->handler;
    ret->presetName = this->presetName;
    return ret;
}

void MagicTowerPassiveObject::onMoveToHandler()
{
    MagicTowerScene* scene = dynamic_cast<MagicTowerScene*>(this->scene());
    if(handler!=NULL)
    {
        handler->onMoveToHandler(scene, this);
    }
}
