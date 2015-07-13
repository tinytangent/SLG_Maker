#include <QMessageBox>
#include <QFileDialog>

#include "SLGMMainWindow.h"
#include "SLGMGameEditorWidget.h"

SLGMMainWindow::SLGMMainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionNew,SIGNAL(triggered(bool)),this,SLOT(onActionNew()));
	editorWidget = new SLGMGameEditorWidget();
	setCentralWidget(editorWidget);
}
void SLGMMainWindow::onActionNew()
{
	QFileDialog fileDialog;
	fileDialog.setFileMode(QFileDialog::ExistingFile);
	fileDialog.setNameFilter("魔塔数据文件 (startup.mtmap.ini)");
	if(fileDialog.exec())
	{
		QStringList temp = fileDialog.selectedFiles();
		QFileInfo info(temp[0]);
		bool confirmLoad = true;
		/*if(gamePath!="")
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
		}*/
		if(confirmLoad)
		{
			//gamePath = info.path();
			//loader.loadGame(gamePath);
			//gamePlayed = false;
		}
	}
}
