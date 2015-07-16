#ifndef _GAME_UNIT_H_
#define _GAME_UNIT_H_

#include <string>
#include <map>
#include "GameEvent.h"
#include "GameBase.h"

using namespace std;

class GameLayerSquare;
class GameUnit : public GameBase
{
	struct Pos
	{
		int x;
		int y;
	};
private:
	Pos position;
	GameLayerSquare* parent;
public:
	GameUnit();
	GameUnit(GameLayerSquare* _parent);
	~GameUnit();

	Pos Position();
	int ChangePosition(int x, int y);
	int ChangePosition(Pos newPos);

	/*
	* @brief 设置父对象
	* @param _parent:要设置为父对象的指针
	* @return 0:设置成功 1:设置失败
	*/
	int SetParent(GameLayerSquare* _parent);
};



#endif
