#include "GameUnit.h"
#include "GameLayerSquare.h"

using namespace std;

//////////////////////////////构造与析构函数//////////////////////////////
GameLayerSquare::GameLayerSquare()
{
	nUnitNumber = 0;
}

GameLayerSquare::GameLayerSquare(GameBoardSquare* _parent)
{
	nUnitNumber = 0;
	parent = _parent;
}


//////////////////////////////子对象管理函数//////////////////////////////
/*
* @brief 将一个已有单位加入GameLayerSquare
*        注意！由于单位(GameUnit)的性质，不允许生成（加入空单位）！同时，加入单位id会自动后延
* @param gameLayer:要加入的单位
* @return 0:成功加入
*/
int GameLayerSquare::AddUnit(GameUnit* newUnit)
{
	unit[nUnitNumber] = newUnit;
	unit[nUnitNumber]->SetParent(this);
	nUnitNumber ++;
	return 0;
}
/*
* @brief 删除一个指定id的单位（令其不接受GameLayerSquare管理），必要时可以将其从内存中删除
*        注意！就算在游戏过程中一个单位被移除（死亡）了，它依然可能对游戏产生影响！
*        所以除非一局游戏彻底结束需要释放内存，否则尽量不要调用该函数！
* @param nId:要删除的单位的id; bDestroy:是否同时从内存中删除
* @return 0:成功删除;
*/
int GameLayerSquare::DeleteUnit(int nId, bool bDestroy)
{
	if (bDestroy)
		delete unit[nId];
	unit.erase(nId);
	nUnitNumber --;
	return 0;
}
/*
* @brief 查询指定id的单位，若存在则提供其指针
* @param nId:要查询的单位的id; result:查询结果
* @return 0:成功查询; 1:不存在同id单位
*/
int GameLayerSquare::QueryUnit(int nId, GameUnit* result)
{
	if (unit.count(nId) == 0)
		return 1;
	result = unit[nId];
	return 0;
}

//////////////////////////////自身操作函数//////////////////////////////
/*
* @brief 设置父对象
* @param _parent:要设置为父对象的指针
* @return 0:设置成功 1:设置失败
*/
int GameLayerSquare::SetParent(GameBoardSquare* _parent)
{
	parent = _parent;
	return 0;
}

/*
* @brief 拓展GameLayerSquare大小
*        注意！由于单独调整一个层的大小会造成与其他层不协调，除特殊情况外本函数只能由ExpandBoard调用！
* @param nNewSizeX,nNewSizeY:新层的大小 nAnchorX,nAnchorY:原坐标(0,0)在新层上的坐标
* @return 0:成功拓展 1:新层的大小比原有大小还要小 2:由于nAnchorX或nAnchorY过大导致原层一部分/全部超出新层范围
*/
int GameLayerSquare::ExpandLayer(int nNewSizeX, int nNewSizeY, int nAnchorX, int nAnchorY)
{
	if (nNewSizeX < nSizeX || nNewSizeY < nSizeY)
		return 1;
	if (nAnchorX + nSizeX > nNewSizeX || nAnchorY + nSizeY > nNewSizeY)
		return 2;
	map<int,GameUnit*>::iterator it;
	for (it = unit.begin(); it != unit.end(); it++)
		it->second->ChangePosition(it->second->Position().x + nAnchorX, it->second->Position().y + nAnchorY);
	return 0;
}
/*
* @brief 缩小GameLayerSquare大小
*        注意！由于单独调整一个层的大小会造成与其他层不协调，除特殊情况外本函数只能由ExpandBoard调用！
*        注意！由于相关机制未完成，这个函数并不完善！
* @param nNewSizeX,nNewSizeY:新层的大小 nAnchorX,nAnchorY:新层上的坐标(0,0)在原层的坐标
* @return 0:成功拓展 1:新层的大小比原有大小还要大 2:由于nAnchorX或nAnchorY过大导致新层一部分/全部超出原层范围
*/
int GameLayerSquare::ShrinkLayer(int nNewSizeX, int nNewSizeY, int nAnchorX, int nAnchorY)
{
	if (nNewSizeX > nSizeX || nNewSizeY > nSizeY)
		return 1;
	if (nAnchorX + nNewSizeX > nSizeX || nAnchorY + nNewSizeY > nSizeY)
		return 2;
	map<int,GameUnit*>::iterator it;
	for (it = unit.begin(); it != unit.end(); it++)
		it->second->ChangePosition(it->second->Position().x - nAnchorX, it->second->Position().y - nAnchorY);
	return 0;
}


//////////////////////////////查询函数//////////////////////////////
int GameLayerSquare::StackOrder()
{
	return nStackOrder;
}

int GameLayerSquare::SizeX()
{
	return nSizeX;
}

int GameLayerSquare::SizeY()
{
	return nSizeY;
}