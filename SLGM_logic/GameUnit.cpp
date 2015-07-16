#include "GameUnit.h"
#include "GameLayerSquare.h"

using namespace std;


//////////////////////////////构造与析构函数//////////////////////////////
GameUnit::GameUnit()
{
}

GameUnit::GameUnit(GameLayerSquare* _parent)
{
	parent = _parent;
}

GameUnit::~GameUnit()
{
}


//////////////////////////////自身操作函数//////////////////////////////
GameUnit::Pos GameUnit::Position()
{
	return position;
}

int GameUnit::ChangePosition(int x, int y)
{
	position.x = x;
	position.y = y;
	return 0;
}

int GameUnit::ChangePosition(Pos newPos)
{
	position = newPos;
	return 0;
}

/*
* @brief 设置父对象
* @param _parent:要设置为父对象的指针
* @return 0:设置成功 1:设置失败
*/
int GameUnit::SetParent(GameLayerSquare* _parent)
{
	parent = _parent;
	return 0;
}
