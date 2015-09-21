#include "SLGCGame.h"
#include "SLGMDlgAddMap.h"
#include "ui_SLGMDlgAddMap.h"
#include <QVariant>

SLGMDlgAddMap::SLGMDlgAddMap(const SLGCGame *_game, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SLGMDlgAddMap)
{
	game = _game;
	ui->setupUi(this);
}

SLGCDict SLGMDlgAddMap::getDlgParameter()
{
	//TODO Just a demo......
	SLGCDict ret;
	ret["mode"] = "clone";
	ret["mapName"] = "AAA";
	ret["cloneFrom"] = ui->comboBox->currentData().toString();
	return ret;
}

SLGMDlgAddMap::~SLGMDlgAddMap()
{
	delete ui;
}

int SLGMDlgAddMap::exec()
{
	ui->comboBox->clear();
	foreach(const QString& mapName, game->allMaps())
	{
		ui->comboBox->addItem(mapName,mapName);
	}
	return QDialog::exec();
}
