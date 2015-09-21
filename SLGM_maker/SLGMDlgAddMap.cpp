#include "SLGMDlgAddMap.h"
#include "ui_SLGMDlgAddMap.h"

SLGMDlgAddMap::SLGMDlgAddMap(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SLGMDlgAddMap)
{
	ui->setupUi(this);
}

SLGMDlgAddMap::~SLGMDlgAddMap()
{
	delete ui;
}
