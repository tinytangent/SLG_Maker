#include "SLGMObjectSelectorWidget.h"
#include "SLGMMainWindow.h"
#include "SLGMEditorWidget.h"
#include "SLGMEditorScene.h"
#include "MagicTowerPassiveObject.h"
#include <QStandardItemModel>

SLGMObjectSelectorWidget::SLGMObjectSelectorWidget(SLGMMainWindow *_mainWindow) : QWidget(_mainWindow)
{
	ui.setupUi(this);
	mainWindow = _mainWindow;
	objectListModel = new QStandardItemModel();
	ui.listViewObject->setModel(objectListModel);
	connect(ui.listViewObject,SIGNAL(clicked(QModelIndex)),this,SLOT(onListViewClicked(QModelIndex)));
	//QStandardItem* item = new QStandardItem("AAAAA");
	//objectListModel->insertRow(0,item);
}

void SLGMObjectSelectorWidget::updateObjectList()
{
	foreach(const QString& presetName, mainWindow->getEditorWidget()->loader->allPresets().keys())
	{
		SLGCGameUnit* obj = mainWindow->getEditorWidget()->loader->getPreset<SLGCGameUnit>(presetName);
		MagicTowerPassiveObject* po = dynamic_cast<MagicTowerPassiveObject*>(obj);
		if(po!=NULL)
		{
			QStandardItem* item = new QStandardItem(presetName);
			item->setIcon(QIcon(*po->animationData[0].pixmap));
			objectListModel->insertRow(0,item);
		}
	}
}

void SLGMObjectSelectorWidget::onListViewClicked(const QModelIndex &index)
{
	QString presetName = objectListModel->itemFromIndex(index)->text();
	mainWindow->getEditorScene()->currentCursorObject = presetName;
}
