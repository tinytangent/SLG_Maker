#ifndef SLGMDLGADDMAP_H
#define SLGMDLGADDMAP_H

#include <QDialog>
#include "SLGCGame.h"

namespace Ui {
class SLGMDlgAddMap;
}

class SLGMDlgAddMap : public QDialog
{
	Q_OBJECT
protected:
	const SLGCGame* game;
public:
	explicit SLGMDlgAddMap(const SLGCGame* _game, QWidget *parent = 0);
	SLGCDict getDlgParameter();
	~SLGMDlgAddMap();

private:
	Ui::SLGMDlgAddMap *ui;

public slots:
	virtual int exec();
};

#endif // SLGMDLGADDMAP_H
