#ifndef NPCDIALOGEXTENSION_H
#define NPCDIALOGEXTENSION_H

#include <QVector>
#include "DialogExtension.h"

class NPCDialogExtension;

class NPCDialogPage
{
public:
    QString titlePixmap;
    //对话框标题
    QString title;

    //对话框内容
    QString content;

    //（可选）商店消耗的玩家属性
    QString costProperty;

    //（可选）商店
    int costValue;

    //（可选）商店价格增加模式
    int costIncreaseMode;

    //（可选）商店价格的增加数值
    int costIncreaseRate;

    //（可选）商店的选择列表
    QStringList options;

    //（可选）商店的可购买属性
    QStringList purchasedProperties;

    //（可选）商店中各个属性可以购买到的数值
    QList<int> purchasedValues;
};

class NPCDialogData : public QObject
{
    Q_OBJECT
protected:
    QVector<NPCDialogPage> dialogPages;
    int cursor;
public:
    NPCDialogData()
    {
        cursor = 0;
    }

    //添加一个页面
    void addPage(const QString& titlePixmap, const QString& title, const QString& content)
    {
        NPCDialogPage page;
        page.titlePixmap = titlePixmap;
        page.title = title;
        page.content = content;
        dialogPages.append(page);
    }
    void addPage(const QString& titlePixmap, const QString& title, const QString& content,
                 const QString& costProperty, int costValue, int costIncreaseMode,int costIncreaseRate,
                 const QStringList& options, const QStringList& purchasedProperties, const QList<int>& purchasedValues)
    {
        NPCDialogPage page;
        page.titlePixmap = titlePixmap;
        page.title = title;
        page.content = content;
        page.options = options;
        page.costProperty = costProperty;
        page.costValue = costValue;
        page.costIncreaseMode = costIncreaseMode;
        page.costIncreaseRate = costIncreaseRate;
        page.purchasedProperties = purchasedProperties;
        page.purchasedValues = purchasedValues;
        dialogPages.append(page);
    }

    //转跳到下一个对话框页面
    bool nextPage()
    {
        if(cursor == dialogPages.size()-1) return false;
        cursor++;
        return true;
    }

    //将对话框回到第一页
    void reset()
    {
        cursor = 0;
    }

    NPCDialogPage& currentPage()
    {
        return dialogPages[cursor];
    }
};

class NPCDialogExtension : public DialogExtension
{
    Q_OBJECT
protected:

    //存储的对话框数据对象
    NPCDialogData* dialogPages;

    //当前选择的选项，仅用于商店页面
    int selectedOption;
public:
    //构造函数
    explicit NPCDialogExtension(SLGMEditorScene* scene);

    //启动NPC对话框
    virtual void beginDialog(NPCDialogData &_dialogPages);

    //键盘按下事件
    virtual void keyPressEvent(QKeyEvent* event);

    //对话框绘制函数
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
signals:

public slots:

};

#endif // NPCDIALOGEXTENSION_H
