#include "GameBoardSquare.h"


//////////////////////////////构造与析构函数//////////////////////////////
GameBoardSquare::GameBoardSquare()
{
	nLayerNumber = 0;
}

GameBoardSquare::GameBoardSquare(Game* _parent)
{
	nLayerNumber = 0;
	parent = _parent;
}


//////////////////////////////子对象管理函数//////////////////////////////
/*
* @brief 生成一个指定名称的新层
* @param sLayerName:新层的名称
* @return 0:成功生成 1:已存在拥有该名称的层
*/
int GameBoardSquare::AddLayer(string sLayerName)
{
	if (layer.count(sLayerName) == 1)
		return 1;
	nLayerNumber ++;
	layer[sLayerName] = new GameLayerSquare(this);
	return 0;
}
/*
* @brief 将一个已有层加入GameBoardSquare
* @param sLayerName:层加入后的名称 gameLayer:要加入的层
* @return 0:成功生成 1:已存在拥有该名称的层
*/
int GameBoardSquare::AddLayer(string sLayerName, GameLayerSquare* gameLayer)
{
	if (layer.count(sLayerName) == 1)
		return 1;
	nLayerNumber ++;
	layer[sLayerName] = gameLayer;
	layer[sLayerName]->SetParent(this);
	return 0;
}
/*
* @brief 从GameBoardSquare中删除一个指定层
*        注意！就算在游戏过程中一个层被移除（死亡）了，它依然可能对游戏产生影响！
*        所以除非一局游戏彻底结束需要释放内存，否则尽量不要调用该函数！
* @param sLayerName:要删除的层的名称; bDestroy:是否同时从内存中删除
* @return 0:成功删除 1:拥有该名称的层不存在
*/
int GameBoardSquare::DeleteLayer(string sLayerName, bool bDestroy = true)
{
	if (layer.count(sLayerName) == 0)
		return 1;
	if (bDestroy)
		delete layer[sLayerName];
	return 0;
}



//////////////////////////////自身操作函数//////////////////////////////
/*
* @brief 拓展GameBoardSquare大小
* @param nNewSizeX,nNewSizeY:新棋盘的大小 nAnchorX,nAnchorY:原坐标(0,0)在新棋盘上的坐标
* @return 0:成功拓展 1:新棋盘的大小比原有大小还要小 2:由于nAnchorX或nAnchorY过大导致原棋盘一部分/全部超出新棋盘范围
*/
int GameBoardSquare::ExpandBoard(int nNewSizeX, int nNewSizeY, int nAnchorX = 0, int nAnchorY = 0)
{
	map<string,GameLayerSquare*>::iterator it;
	for (it = layer.begin(); it != layer.end(); it++)
	{
		if (it->second->ExpandLayer(nNewSizeX, nNewSizeY, nAnchorX, nAnchorY) != 0)
			return it->second->ExpandLayer(nNewSizeX, nNewSizeY, nAnchorX, nAnchorY);
	}
	return 0;
}
/*
* @brief 缩小GameBoardSquare大小
* @param nNewSizeX,nNewSizeY:新棋盘的大小 nAnchorX,nAnchorY:新棋盘(0,0)在原棋盘上的坐标
* @return 0:成功拓展 1:新棋盘的大小比原有大小还要大 2:由于nAnchorX或nAnchorY过大导致新棋盘一部分/全部超出原棋盘范围
*/
int GameBoardSquare::ShrinkBoard(int nNewSizeX, int nNewSizeY, int nAnchorX = 0, int nAnchorY = 0)
{
	map<string,GameLayerSquare*>::iterator it;
	for (it = layer.begin(); it != layer.end(); it++)
	{
		if (it->second->ShrinkLayer(nNewSizeX, nNewSizeY, nAnchorX, nAnchorY) != 0)
			return it->second->ShrinkLayer(nNewSizeX, nNewSizeY, nAnchorX, nAnchorY);
	}
	return 0;
}

int GameBoardSquare::SetParent(Game* _parent)
{
	parent = _parent;
	return 0;
}

//////////////////////////////查询函数//////////////////////////////
/*
* @brief 查询该棋盘中是否有指定名称的层，若有则返回指向它的指针
* @param sLayerName:要查询的层的名称; result:查询到的指针
* @return 0: 1:没有该名称的层指向要查询的层的指针
*/
int GameBoardSquare::QueryLayer(string sLayerName, GameLayerSquare* result)
{
	if (layer.count(sLayerName) == 0)
		return 1;
	result = layer[sLayerName];
	return 0;
}


int GameBoardSquare::SizeX()
{
	return nSizeX;
}
int GameBoardSquare::SizeY()
{
	return nSizeY;
}