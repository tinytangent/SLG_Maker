#ifndef SLGMMAPTREEEDITOR_H
#define SLGMMAPTREEEDITOR_H

#include <QWidget>

class SLGCGame;
class SLGMDlgAddMap;

namespace Ui {
class SLGMMapTreeEditor;
}

class SLGMMapTreeEditor : public QWidget
{
	Q_OBJECT
protected:
	SLGCGame* game;
	SLGMDlgAddMap* dlgAddMap;
public:
	explicit SLGMMapTreeEditor(SLGCGame* _game, QWidget *parent = 0);
	~SLGMMapTreeEditor();
	void loadGameHierarchy();
private:
	Ui::SLGMMapTreeEditor *ui;
public slots:
	void onAddMap();
	void onAddLayer();
};

#endif // SLGMMAPTREEEDITOR_H
