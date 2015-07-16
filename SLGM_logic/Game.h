#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <map>
#include "GameBoardSquare.h"
#include "GameEvent.h"
#include "GameBase.h"

using namespace std;

/*
* @brief
* Game类是逻辑部分的组成模块，它负责实现一局游戏。
* 一局游戏至少会含有一个棋盘，Game类负责管理它（们）。
* 同时，Game也会管理一些属于自身的变量
*/
class Game : public GameBase
{
private:
	//Game管理的GameBoard的数量
	int nBoardNumber;
	//被Game管理的GameBoardquare
	map<string,GameBoardSquare*> gameBoardSquare;

	//bgm状态，控制bgm的播放
	//其值为所要（正在）播放bgm的序号，取-1时表示不播放
	int nBGMStatus;

public:
	/*
	* @brief 更改播放的bgm序号
	* @param nBGMSerial:想要更改的值
	* @return 0:更改成功
	*/
	int SwitchBGM(int nBGMSerial);

	/*
	* @brief 新建一个GameBoardSquare或指定一个已有GameBoardSquare，令其接受Game的管理并命名
	* @param sBoardName:要加入的GameBoardSquare的名字; newGameBoardSquare:指向要加入的GameBoardSquare的指针
	* @return 0:成功新建/加入; 1:已存在同名GameBoardSquare，新建/加入失败
	*/
	int AddGameBoardSquare(string sBoardName, GameBoardSquare* newGameBoardSquare = NULL);
	/*
	* @brief 删除一个指定的GameBoardSquare（令其不接受Game管理），必要时可以将其从内存中删除
	*        注意！就算在游戏过程中一个GameBoardSquare被移除（死亡）了，它依然可能对游戏产生影响！
	*        所以除非一局游戏彻底结束需要释放内存，否则尽量不要调用该函数！
	* @param sBoardName:要删除的GameBoardSquare的名字; bDestroy:是否同时从内存中删除
	* @return 0:成功删除; 1:不存在同名GameBoardSquare，删除失败
	*/
	int DeleteGameBoardSquare(string sBoardName, bool bDestroy = true);
	/*
	* @brief 查询指定名称的GameBoardSquare，若存在则提供其指针
	* @param sBoardName:要查询的GameBoardSquare的名称; result:查询结果
	* @return 0:成功查询; 1:不存在同名GameBoardSquare
	*/
	int QueryGameBoardSquare(string sBoardName, GameBoardSquare* result);
};


#endif
