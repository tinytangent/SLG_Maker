/**************************************************************************

Copyright:Sunburst

Author:廖亦阳

Date:2015-03-29

Description:实现了GameBoardSquare类。

**************************************************************************/

#ifndef _GAME_BOARD_SQUARE_H_
#define _GAME_BOARD_SQUARE_H_

#include <string>
#include <map>
#include "GameBase.h"
#include "GameLayerSquare.h"
#include "GameEvent.h"
#include "Game.h"

using namespace std;

/*
* @brief
* GameBoardSquare类是逻辑部分的组成模块，它负责实现并储存正方形格棋盘。
* 由于一个棋盘实际上是由多个重叠的层（如单位、地形等）组成的，所以GameBoardSquare实际上负责管理这些层。
* 同时，GameBoardSquare也会管理一些属于自身的变量（比如自己的名称）
*/
class GameBoardSquare : public GameBase
{
private:
	//棋盘大小
	int nSizeX;
	int nSizeY;
	//该棋盘所管理的层
	map<string,GameLayerSquare*> layer;

	int nLayerNumber;

	Game* parent;

public:
	//构造函数
	GameBoardSquare();
	GameBoardSquare(Game* _parent);
	//析构函数
	~GameBoardSquare();

	/*
	* @brief 生成一个指定名称的新层
	* @param sLayerName:新层的名称
	* @return 0:成功生成 1:已存在拥有该名称的层
	*/
	int AddLayer(string sLayerName);

	/*
	* @brief 将一个已有层加入GameBoardSquare
	* @param sLayerName:层加入后的名称 gameLayer:要加入的层
	* @return 0:成功生成 1:已存在拥有该名称的层
	*/
	int AddLayer(string sLayerName, GameLayerSquare* gameLayer);

	/*
	* @brief 从GameBoardSquare中删除一个指定层，必要时可以将其从内存中删除
	*        注意！就算在游戏过程中一个层被移除（死亡）了，它依然可能对游戏产生影响！
	*        所以除非一局游戏彻底结束需要释放内存，否则尽量不要调用该函数！
	* @param sLayerName:要删除的层的名称; bDestroy:是否同时从内存中删除
	* @return 0:成功删除 1:拥有该名称的层不存在
	*/
	int DeleteLayer(string sLayerName, bool bDestroy = true);

	/*
	* @brief 拓展GameBoardSquare大小
	* @param nNewSizeX,nNewSizeY:新棋盘的大小 nAnchorX,nAnchorY:原坐标(0,0)在新棋盘上的坐标
	* @return 0:成功拓展 1:新棋盘的大小比原有大小还要小 2:由于nAnchorX或nAnchorY过大导致原棋盘一部分/全部超出新棋盘范围
	*/
	int ExpandBoard(int nNewSizeX, int nNewSizeY, int nAnchorX = 0, int nAnchorY = 0);

	/*
	* @brief 缩小GameBoardSquare大小
	* @param nNewSizeX,nNewSizeY:新棋盘的大小 nAnchorX,nAnchorY:新棋盘(0,0)在原棋盘上的坐标
	* @return 0:成功拓展 1:新棋盘的大小比原有大小还要大 2:由于nAnchorX或nAnchorY过大导致新棋盘一部分/全部超出原棋盘范围
	*/
	int ShrinkBoard(int nNewSizeX, int nNewSizeY, int nAnchorX = 0, int nAnchorY = 0);

	/*
	* @brief 查询该棋盘中是否有指定名称的层，若有则返回指向它的指针
	* @param sLayerName:要查询的层的名称; result:查询到的指针
	* @return 0: 1:没有该名称的层指向要查询的层的指针
	*/
	int QueryLayer(string sLayerName, GameLayerSquare* result);
	
	/*
	* @brief 设置父对象
	* @param _parent:要设置为父对象的指针
	* @return 0:设置成功 1:设置失败
	*/
	int SetParent(Game* _parent);

	int SizeX();
	int SizeY();
};

#endif