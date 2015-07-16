#include "SLGMObjectSelectorWidget.h"
#include "SLGMMainWindow.h"
#include "SLGMEditorWidget.h"
#include "MagicTowerObject.h"
#include <QStandardItemModel>

SLGMObjectSelectorWidget::SLGMObjectSelectorWidget(SLGMMainWindow *_mainWindow) : QWidget(_mainWindow)
{
	ui.setupUi(this);
	mainWindow = _mainWindow;
	objectListModel = new QStandardItemModel();
	ui.listViewObject->setModel(objectListModel);
	//QStandardItem* item = new QStandardItem("AAAAA");
	//objectListModel->insertRow(0,item);
}

void SLGMObjectSelectorWidget::updateObjectList()
{
	foreach(const QString& presetName, mainWindow->getEditorWidget()->loader->allPresets().keys())
	{
		MagicTowerObject* obj = mainWindow->getEditorWidget()->loader->getPreset<MagicTowerObject>(presetName);
		if(obj!=NULL)
		{
			QStandardItem* item = new QStandardItem(presetName);
			objectListModel->insertRow(0,item);
		}
	}
}
