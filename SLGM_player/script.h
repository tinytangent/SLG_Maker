#ifndef SCRIPT_H
#define SCRIPT_H

#include "MagicTowerScene.h"
#include "MagicTowerCharacter.h"
#include "MagicTowerObject.h"
#include "ResourceManager.h"
#include "MagicTowerPassiveObject.h"
#include "CharacterPropertyExtension.h"
#include "DialogExtension.h"
#include "CharacterPropertyExtension.h"
#include "CombatDialogExtension.h"
#include "NPCDialogExtension.h"
#include "MagicTowerLoader.h"
#include "SaveLoadExtension.h"

/**
 * @brief GeneralItemHandler is used to handle all Items that is used to increase or decrease some
 * properties of a character.
 * （说起来有一点抽象，其实钥匙，血瓶，门，宝石都是这一类的物品）
 */
class GeneralItemHandler : public MTPOEHandler
{
protected:
    bool disappearing;
public:
    QString appliedGameProperty;
    int appliedPropertyDelta;
    virtual bool onAttemptMoveHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj)
    {
        MagicTowerCharacter* currentCharacter = scene->getActiveCharacter();
        if(currentCharacter!=NULL)
        {
            int temp = currentCharacter->getGameProperty(appliedGameProperty);
            temp += appliedPropertyDelta;
            if(temp<0) return false;
            currentCharacter->setGameProperty(appliedGameProperty,temp);
        }
        scene->getExtension<CharacterPropertyExtension>("characterProperty")->update();
        scene->setObjectAt(obj->getMap(),obj->getLayer(),obj->getGridX(),obj->getGridY(),NULL);
        return false;
    }

    virtual void onMoveToHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj)
    {

    }

    GeneralItemHandler(const QString& _property,const int _delta)
    {
        appliedGameProperty = _property;
        appliedPropertyDelta = _delta;
        //disappearing = false;
    }
};

/**
 * @brief MonsterHandler类用于处理怪物类对象的事件
 */
class MonsterHandler : public MTPOEHandler
{
public:
    QString appliedGameProperty;
    int appliedPropertyDelta;
    virtual bool onAttemptMoveHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj)
    {
        scene->getExtension<CombatDialogExtension>("combatDialog")->beginFight(scene->getActiveCharacter(),obj);
        return false;
    }

    virtual void onMoveToHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj)
    {
    }
};

/**
 * @brief TransporterHandler处理传送点对象（比如楼梯）
 */
class TransporterHandler : public MTPOEHandler
{
public:
    QString targetMap;
    QString targetLayer;
    int targetX;
    int targetY;
    virtual bool onAttemptMoveHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj)
    {
        Q_UNUSED(scene);
        Q_UNUSED(obj);
        return true;
    }

    virtual void onMoveToHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj)
    {
        MagicTowerCharacter* character = scene->getActiveCharacter();
        if(character == NULL) return;
		// Maybe we need some more music here?
        scene->setObjectAt(character, NULL, false);
        scene->setObjectAt(targetMap, targetLayer, targetX, targetY, character);
        scene->setActiveCharacter(character);
        scene->getExtension<CharacterPropertyExtension>("characterProperty")->update();
    }
    TransporterHandler(const QString& _targetMap, const QString& _targetLayer, int _targetX, int _targetY):
        targetMap(_targetMap),
        targetLayer(_targetLayer),
        targetX(_targetX),
        targetY(_targetY)
    {
    }

};

/**
 * @brief NPCHandler类处理NPC对象
 */
class NPCHandler : public MTPOEHandler
{
public:
    NPCDialogData* data;
    NPCHandler(NPCDialogData& _data)
    {
        data = &_data;
    }

    virtual bool onAttemptMoveHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj)
    {
        Q_UNUSED(scene);
        Q_UNUSED(obj);
        scene->getExtension<NPCDialogExtension>("npcDialog")->beginDialog(*data);
        return false;
    }

    virtual void onMoveToHandler(MagicTowerScene* scene, MagicTowerPassiveObject* obj)
    {
        Q_UNUSED(scene);
        Q_UNUSED(obj);
    }
};

void loadMap(MagicTowerScene* scene);

#endif // SCRIPT_H
