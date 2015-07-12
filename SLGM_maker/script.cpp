#include "script.h"
#include <QFileDialog>
void loadMap(MagicTowerScene* scene)
{
    scene->addExtension<CharacterPropertyExtension>("characterProperty");
    scene->addExtension<DialogExtension>("dialog");
    scene->addExtension<CombatDialogExtension>("combatDialog");
    scene->getExtension<CharacterPropertyExtension>("characterProperty")->update();
    scene->addExtension<NPCDialogExtension>("npcDialog");
    scene->addExtension<SaveLoadExtension>("saveLoad");
}
