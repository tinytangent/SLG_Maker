#ifndef SLGMMAPTREEEDITOR_H
#define SLGMMAPTREEEDITOR_H

#include <QWidget>

class SLGCGame;

namespace Ui {
class SLGMMapTreeEditor;
}

class SLGMMapTreeEditor : public QWidget
{
	Q_OBJECT
protected:
	SLGCGame* game;
public:
	explicit SLGMMapTreeEditor(SLGCGame* _game, QWidget *parent = 0);
	~SLGMMapTreeEditor();
	void loadGameHierarchy();
private:
	Ui::SLGMMapTreeEditor *ui;
};

#endif // SLGMMAPTREEEDITOR_H
