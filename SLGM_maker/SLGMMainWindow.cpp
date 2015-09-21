#include <QMessageBox>
#include <QHBoxLayout>

#include "SLGMMainWindow.h"
#include "SLGMEditorWidget.h"
#include "SLGMEditorScene.h"
#include "SLGMObjectSelectorWidget.h"
#include "SLGMMapTreeEditor.h"

SLGMMainWindow::SLGMMainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionNew,SIGNAL(triggered()),this,SLOT(onActionNew()));
	connect(ui.actionOpen,SIGNAL(triggered()),this,SLOT(onActionOpen()));
	connect(ui.actionSave,SIGNAL(triggered()),this,SLOT(onActionSave()));
	connect(ui.actionSaveAs,SIGNAL(triggered()),this,SLOT(onActionSaveAs()));
	connect(ui.actionClose,SIGNAL(triggered()),this,SLOT(onActionClose()));
	mainLayout = new QHBoxLayout();
	editorWidget = new SLGMEditorWidget();
	widgetMapTreeEditor = new SLGMMapTreeEditor(this->getEditorScene()->game, this);
	objectSelectorWidget = new SLGMObjectSelectorWidget(this);
	mainLayout->addWidget(widgetMapTreeEditor);
	mainLayout->addWidget(editorWidget);
	mainLayout->addWidget(objectSelectorWidget);
	QWidget* temp = new QWidget();
	temp->setLayout(mainLayout);
	setCentralWidget(temp);
}

SLGMEditorWidget* SLGMMainWindow::getEditorWidget()
{
	return this->editorWidget;
}

SLGMEditorScene* SLGMMainWindow::getEditorScene()
{
	return this->editorWidget->gameScene;
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
	objectSelectorWidget->updateObjectList();
	widgetMapTreeEditor->loadGameHierarchy();
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
