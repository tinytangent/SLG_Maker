#include "NPCDialogExtension.h"
#include "MagicTowerCharacter.h"
#include "CharacterPropertyExtension.h"
#include "SaveLoadExtension.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>

NPCDialogExtension::NPCDialogExtension(MagicTowerScene *scene) :
    DialogExtension(scene)
{
    dialogPages = NULL;
}

void NPCDialogExtension::beginDialog(NPCDialogData &_dialogPages)
{
    dialogPages = &_dialogPages;
    selectedOption = 0;
    dialogPages->reset();
    showDialog();
}

void NPCDialogExtension::keyPressEvent(QKeyEvent* event)
{
    NPCDialogPage& currentPage = dialogPages->currentPage();
    switch(event->key())
    {
    case Qt::Key_Space:
    case Qt::Key_Return:
        if(dialogPages->currentPage().options.size()>0)
        {
            if(dialogPages->currentPage().purchasedProperties[selectedOption] == "exit")
            {
                hideDialog();
                break;
            }
            NPCDialogPage& currentPage = dialogPages->currentPage();
            int characterPropertyVal = magicTowerScene->getActiveCharacter()->getIntGameProperty(currentPage.costProperty);
            int characterPurchasedPropertyVal = magicTowerScene->getActiveCharacter()->getIntGameProperty(
                        currentPage.purchasedProperties[selectedOption]);
            characterPropertyVal -= currentPage.costValue;
            characterPurchasedPropertyVal += currentPage.purchasedValues[selectedOption];
            if(characterPropertyVal < 0) break;
            magicTowerScene->getActiveCharacter()->setGameProperty(currentPage.costProperty, characterPropertyVal);
            magicTowerScene->getActiveCharacter()->setGameProperty(currentPage.purchasedProperties[selectedOption], characterPurchasedPropertyVal);
            magicTowerScene->getExtension<CharacterPropertyExtension>("characterProperty")->update();
        }
        else if(dialogPages->currentPage().title == "ending" && dialogPages->currentPage().content == "ending")
        {
            QMessageBox::information(NULL,"游戏结束","祝贺您，成功完成了游戏！");
            hideDialog();
            magicTowerScene->reset();
            magicTowerScene->getExtension<SaveLoadExtension>("saveLoad")->active();
        }
        else if(!dialogPages->nextPage())
        {
            hideDialog();
        }
        else update();
        break;
    case Qt::Key_Up:
        if(selectedOption>0)
            selectedOption--;
        break;
    case Qt::Key_Down:
        if(selectedOption<currentPage.options.size()-1)
            selectedOption++;
        break;
    }
    update();

}

void NPCDialogExtension::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    setDialogSize(QSize(400,200));
    DialogExtension::paint(painter, option, widget);
    QFont textFont("黑体", 14);
    painter->setFont(textFont);
    painter->setPen(QPen(Qt::white));
    painter->setBrush(QBrush(Qt::white));
    if(dialogPages == NULL) return;
    NPCDialogPage& page = dialogPages->currentPage();
    painter->drawText(QRect(50,0,300,100),QString("标题:%1").arg(page.title));
    painter->drawText(QRect(50,20,300,100),QString("内容:%1").arg(page.content));
    painter->drawText(QRect(50,40,300,100),QString("Press any key to continue"));
    if(!page.options.empty())
    {
        for(int i=0;i<page.options.size();i++)
        {
            if(i==selectedOption)
            {
                painter->drawText(QRect(50,60+20*i,300,100),QString("选项**:%1").arg(page.options[i]));
            }
            else
            {
                painter->drawText(QRect(50,60+20*i,300,100),QString("选项:%1").arg(page.options[i]));
            }
        }
    }
}
