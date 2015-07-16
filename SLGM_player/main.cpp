#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "MagicTowerScene.h"
#include "MagicTowerObject.h"
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    SLGMEditorScene scene;
    return app.exec();
}
