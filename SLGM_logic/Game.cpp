#include <string>
#include <map>
#include "Game.h"

using namespace std;


//////////////////////////////构造与析构函数//////////////////////////////




//////////////////////////////自身操作函数//////////////////////////////
/*
* @brief 更改播放的bgm序号
* @param nBGMSerial:想要更改的值
* @return 0:更改成功
*/
int Game::SwitchBGM(int nBGMSerial)
{
	nBGMStatus = nBGMSerial;
	return 0;
}



//////////////////////////////子对象管理函数//////////////////////////////
/*
* @brief 新建一个GameBoardSquare或指定一个已有GameBoardSquare，令其接受Game的管理并命名
* @param sBoardName:要加入的GameBoardSquare的名字; gameBoardSquare:指向要加入的GameBoardSquare的指针
* @return 0:成功新建/加入; 1:已存在同名GameBoardSquare，新建/加入失败
*/
int Game::AddGameBoardSquare(string sBoardName, GameBoardSquare* newGameBoardSquare = NULL)
{
	if (gameBoardSquare.count(sBoardName) == 1)
		return 1;
	if (newGameBoardSquare == NULL)
		gameBoardSquare[sBoardName] = new GameBoardSquare(this);
	else
	{
		gameBoardSquare[sBoardName] = newGameBoardSquare;
		gameBoardSquare[sBoardName]->SetParent(this);
	}
	nBoardNumber ++;
	return 0;
}

/*
* @brief 删除一个指定的GameBoardSquare（令其不接受Game管理），必要时可以将其从内存中删除
*        注意！就算在游戏过程中一个GameBoardSquare被移除（死亡）了，它依然可能对游戏产生影响！
*        所以除非一局游戏彻底结束，否则尽量不要令destroy=1！
* @param sBoardName:要删除的GameBoardSquare的名字; bDestroy:是否同时从内存中删除
* @return 0:成功删除; 1:不存在同名GameBoardSquare，删除失败
*/
int Game::DeleteGameBoardSquare(string sBoardName, bool bDestroy = true)
{
	if (gameBoardSquare.count(sBoardName) == 0)
		return 1;
	if (bDestroy)
		delete gameBoardSquare[sBoardName];
	gameBoardSquare.erase(sBoardName);
	nBoardNumber --;
	return 0;
}

/*
* @brief 查询指定名称的GameBoardSquare，若存在则提供其指针
* @param sBoardName:要查询的GameBoardSquare的名称; result:查询结果
* @return 0:成功查询; 1:不存在同名GameBoardSquare
*/
int Game::QueryGameBoardSquare(string sBoardName, GameBoardSquare* result)
{
	if (gameBoardSquare.count(sBoardName) == 0)
		return 1;
	result = gameBoardSquare[sBoardName];
	return 0;
}