#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "SLGMEditorScene.h"
#include "SLGCGameUnit.h"
#include "SLGMMainWindow.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
	SLGMMainWindow mainWindow;
	mainWindow.show();
	//MagicTowerScene scene;
    return app.exec();
}
