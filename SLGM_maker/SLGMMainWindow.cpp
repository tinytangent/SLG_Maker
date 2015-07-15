#include <QMessageBox>
#include <QFileDialog>

#include "SLGMMainWindow.h"
#include "SLGMEditorWidget.h"

SLGMMainWindow::SLGMMainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionNew,SIGNAL(triggered()),this,SLOT(onActionNew()));
	connect(ui.actionOpen,SIGNAL(triggered()),this,SLOT(onActionOpen()));
	connect(ui.actionSave,SIGNAL(triggered()),this,SLOT(onActionSave()));
	connect(ui.actionSaveAs,SIGNAL(triggered()),this,SLOT(onActionSaveAs()));
	connect(ui.actionClose,SIGNAL(triggered()),this,SLOT(onActionClose()));
	editorWidget = new SLGMGameEditorWidget();
	setCentralWidget(editorWidget);
}
void SLGMMainWindow::onActionNew()
{
}

void SLGMMainWindow::onActionOpen()
{
	fileDialog.setFileMode(QFileDialog::ExistingFile);
	fileDialog.setNameFilter("魔塔数据文件 (startup.mtmap.ini)");
	if(fileDialog.exec())
	{
		QStringList temp = fileDialog.selectedFiles();
		QFileInfo info(temp[0]);
		bool confirmLoad = true;
		if(confirmLoad)
		{
			editorWidget->loadGame(info.path());
		}
	}
}

void SLGMMainWindow::onActionClose()
{

}

void SLGMMainWindow::onActionSave()
{

}

void SLGMMainWindow::onActionSaveAs()
{

}
