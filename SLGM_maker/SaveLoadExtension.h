#ifndef SAVELOADEXTENSION_H
#define SAVELOADEXTENSION_H

#include "MagicTowerExtension.h"
#include <QtWidgets>
#include "MagicTowerLoader.h"

class SaveLoadExtension :public MagicTowerExtension
{
    Q_OBJECT
protected:

    //当前加载的游戏数据文件的路径
    QString gamePath;

    //当前游戏是刚刚被加载还是已经玩过
    bool gamePlayed;

    //内含的魔塔加载器对象
    MagicTowerLoader loader;

    //弹出的对话框
    QDialog* saveLoadDialog;

    //对话框的垂直盒布局
    QVBoxLayout* layout;

    //显示游戏加载状态的标签
    QLabel* labelLoadState;

    //加载游戏按钮
    QPushButton* buttonLoadGame;

    //读取已经保存的游戏的按钮
    QPushButton* buttonLoadSaved;

    //保存游戏的按钮
    QPushButton* buttonSaveGame;

    //开始游戏按钮
    QPushButton* buttonStartNewGame;

    //退出按钮
    QPushButton* buttonExit;
public:
    //构造函数
    explicit SaveLoadExtension(MagicTowerScene* scene);

    //激活暂停对话框
    void active();

    //关闭暂停对画框
    void deactive();
public slots:
    //用于处理各个按钮按下事件的slots
    void onButtonLoadGamePressed();
    void onButtonStartNewGamePressed();
    void onButtonExitPressed();
    void onButtonSaveGamePressed();
    void onButtonLoadSavedGame();
    void updateWidgets();
};

#endif // SAVELOADEXTENSION_H
