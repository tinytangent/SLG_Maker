#include "SaveLoadExtension.h"
#include "MagicTowerCharacter.h"
#include "DialogExtension.h"
#include "NPCDialogExtension.h"
#include "CombatDialogExtension.h"
#include "CharacterPropertyExtension.h"
#include "SLGCGame.h"
SaveLoadExtension::SaveLoadExtension(SLGMEditorScene* scene)
    :MagicTowerExtension(scene),loader(scene)
{
    setZValue(-100);
	saveLoadDialog = new QDialog(/*scene->getParentWidget()*/);
    saveLoadDialog->setMinimumSize(200,300);
    saveLoadDialog->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    saveLoadDialog->open();
    layout = new QVBoxLayout();
    saveLoadDialog->setLayout(layout);
    buttonLoadGame = new QPushButton("加载魔塔数据文件");
    buttonStartNewGame = new QPushButton("开始新游戏");
    buttonSaveGame = new QPushButton("存储游戏");
    buttonLoadSaved = new QPushButton("读取存档");
    buttonExit = new QPushButton("退出游戏");
    labelLoadState = new QLabel("当前未加载任何游戏");
    labelLoadState->setLineWidth(200);
    layout->addWidget(labelLoadState);
    layout->addWidget(buttonLoadGame);
    layout->addWidget(buttonStartNewGame);
    layout->addWidget(buttonSaveGame);
    layout->addWidget(buttonLoadSaved);
    layout->addWidget(buttonExit);
    connect(buttonLoadGame,SIGNAL(pressed()),this,SLOT(onButtonLoadGamePressed()));
    connect(buttonStartNewGame,SIGNAL(pressed()),this,SLOT(onButtonStartNewGamePressed()));
    connect(buttonSaveGame,SIGNAL(pressed()),this,SLOT(onButtonSaveGamePressed()));
    connect(buttonExit,SIGNAL(pressed()),this,SLOT(onButtonExitPressed()));
    connect(buttonLoadSaved,SIGNAL(pressed()),this,SLOT(onButtonLoadSavedGame()));
    updateWidgets();
    gamePlayed = false;
}

void SaveLoadExtension::onButtonLoadGamePressed()
{
    QFileDialog fileDialog(saveLoadDialog);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter("魔塔数据文件 (startup.mtmap.ini)");
    if(fileDialog.exec())
    {
        QStringList temp = fileDialog.selectedFiles();
        QFileInfo info(temp[0]);
        bool confirmLoad = true;
        if(gamePath!="")
        {
            QMessageBox::StandardButton button = QMessageBox::warning(saveLoadDialog,
                                                                      QString("确认加载游戏"),
                                                                      QString("确实要加载新游戏吗？您将会丢失当前游戏的所有进度！"),QMessageBox::Yes|QMessageBox::No);
            if(button == QMessageBox::No)
            {
                confirmLoad = false;
            }
            else
            {
                loader.unloadGame();
            }
        }
        if(confirmLoad)
        {
            gamePath = info.path();
            loader.loadGame(gamePath);
            gamePlayed = false;
        }
    }
    updateWidgets();
}

void SaveLoadExtension::updateWidgets()
{
    if(gamePath=="")
    {
        labelLoadState->setText("当前未加载任何游戏");
        buttonStartNewGame->setEnabled(false);
        buttonLoadSaved->setEnabled(false);
        buttonSaveGame->setEnabled(false);
        if(!gamePlayed)
        {
            buttonSaveGame->setEnabled(false);
        }
    }
    else
    {
        labelLoadState->setText("加载了游戏：" + gamePath);
        buttonStartNewGame->setEnabled(true);
        buttonLoadSaved->setEnabled(true);
        buttonSaveGame->setEnabled(true);
    }
}

void SaveLoadExtension::onButtonStartNewGamePressed()
{
    if(gamePlayed)
    {
        QMessageBox::StandardButton button = QMessageBox::warning(saveLoadDialog,
                                                              QString("确认新建游戏"),
                                                              QString("确实要开始新游戏吗？您将会丢失当前游戏的所有进度！"),QMessageBox::Yes|QMessageBox::No);
        if(button != QMessageBox::Yes) return;
        else magicTowerScene->reset();
    }
    loader.loadMap(gamePath + "/startup.mtmap.ini");
    MagicTowerCharacter* obj2= (MagicTowerCharacter*)loader.getPreset<MagicTowerCharacter>("warrior")->clone();
	magicTowerScene->setObjectAt("1F","character",6,11,obj2);
    magicTowerScene->setActiveCharacter(obj2);
    deactive();
    gamePlayed = true;
}

void SaveLoadExtension::onButtonExitPressed()
{
    QMessageBox::StandardButton button = QMessageBox::warning(saveLoadDialog,
                                                          QString("确认退出游戏"),
                                                          QString("真的要退出吗？您将会丢失当前游戏的所有进度！"),QMessageBox::Yes|QMessageBox::No);
    if(button == QMessageBox::Yes)
    {
        magicTowerScene->clear();
        QApplication::exit(0);
    }
}

void SaveLoadExtension::active()
{
    saveLoadDialog->show();
    updateWidgets();
}

void SaveLoadExtension::deactive()
{
    saveLoadDialog->hide();
}

void SaveLoadExtension::onButtonSaveGamePressed()
{
    QFileDialog fileDialog(saveLoadDialog);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setNameFilter("魔塔存档文件 (*.mtsavedmap.ini)");
    if(!fileDialog.exec())
    {
        return;
    }
    QStringList temp = fileDialog.selectedFiles();
    QFileInfo info(temp[0]);
    loader.saveGame(info.path(),info.baseName());
    QMessageBox::information(saveLoadDialog,"保存游戏成功","保存游戏成功");
}

void SaveLoadExtension::onButtonLoadSavedGame()
{
    QFileDialog fileDialog(saveLoadDialog);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter("魔塔存档文件 (*.mtsavedmap.ini)");
    if(!fileDialog.exec())
    {
        return;
    }
    QStringList temp = fileDialog.selectedFiles();
    QFileInfo info(temp[0]);
    if(gamePlayed)
    {
        QMessageBox::StandardButton button = QMessageBox::warning(saveLoadDialog,
                                                              QString("确认读取存档"),
                                                              QString("确实读取存档吗？当前的游戏状态将丢失！"),QMessageBox::Yes|QMessageBox::No);
        if(button != QMessageBox::Yes) return;
    }
    loader.loadSavedGame(info.path(),info.baseName());
    gamePlayed = true;
    deactive();
}
