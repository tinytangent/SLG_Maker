#ifndef SLGMDLGADDMAP_H
#define SLGMDLGADDMAP_H

#include <QDialog>

namespace Ui {
class SLGMDlgAddMap;
}

class SLGMDlgAddMap : public QDialog
{
	Q_OBJECT

public:
	explicit SLGMDlgAddMap(QWidget *parent = 0);
	~SLGMDlgAddMap();

private:
	Ui::SLGMDlgAddMap *ui;
};

#endif // SLGMDLGADDMAP_H
