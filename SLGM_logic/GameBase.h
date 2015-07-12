#ifndef _GAME_H_
#define _GAME_H

#include <string>
#include <map>
#include "GameEvent.h"

using namespace std;

/*
* @brief
* Game类是逻辑部分的组成模块，由于数个类之间的功能重复，所以这个基类就诞生了。
* 由于重复的功能主要集中于自身变量的管理部分与事件的管理，所以这个基类只实现了这一部分的功能。
*/
class GameBase
{
private:
	//属于自身的事件
	map<int,GameEvent*> event;

	//属于自身的整形
	map<string,int> nProperty;
	//属于自身的浮点
	map<string,double> dProperty;
	//属于自身的字符串
	map<string,string> sProperty;

public:	
//////////////////////////////自身操作函数//////////////////////////////
	/*
	* @brief 新建指定名称的属于自身的整形并赋值
	* @param sPropertyName:变量名; nValue:变量值
	* @return 0:成功新建; 1:已存在同名整形; 2:已存在同名浮点数; 3:已存在同名字符串
	*/
	int AddProperty(string sPropertyName, int nValue);
	/*
	* @brief 新建指定名称的属于自身的整形并赋值
	* @param sPropertyName:变量名; dValue:变量值
	* @return 0:成功新建; 1:已存在同名整形; 2:已存在同名浮点数; 3:已存在同名字符串
	*/
	int AddProperty(string sPropertyName, double dValue);
	/*
	* @brief 新建指定名称的属于自身的整形并赋值
	* @param sPropertyName:变量名;sValue:变量值
	* @return 0:成功新建; 1:已存在同名整形; 2:已存在同名浮点数; 3:已存在同名字符串
	*/
	int AddProperty(string sPropertyName, string sValue);
	/*
	* @brief 删除指定名称的属于自身的变量
	*        注意！就算在游戏过程中一个变量被删除了，它依然可能对游戏产生影响！
	*        所以除非一局游戏彻底结束需要释放内存，否则尽量不要调用该函数！
	* @param sPropertyName:变量名
	* @return 0:成功删除; 1:不存在同名变量
	*/
	int DeleteProperty(string sPropertyName);
	/*
	* @brief 更改指定名称的属于自身的整形的值
	* @param sPropertyName:变量名; nValue:变量值
	* @return 0:成功新建; 1:不存在同名整形;
	*/
	int ChangeProperty(string sPropertyName, int nValue);
	/*
	* @brief 更改指定名称的属于自身的浮点数的值
	* @param sPropertyName:变量名; dValue:变量值
	* @return 0:成功新建; 1:不存在同名整形;
	*/
	int ChangeProperty(string sPropertyName, double dValue);
	/*
	* @brief 更改指定名称的属于自身的字符串的值
	* @param sPropertyName:变量名; sValue:变量值
	* @return 0:成功新建; 1:不存在同名整形;
	*/
	int ChangeProperty(string sPropertyName, string sValue);
	/*
	* @brief 查询指定名称的属于自身的整形的值
	* @param sPropertyName:变量名; nValue:查询到的变量值
	* @return 0:成功查询; 1:不存在同名整形;
	*/

//////////////////////////////查询函数//////////////////////////////
	int QueryProperty(string sPropertyName, int* nValue);
	/*
	* @brief 查询指定名称的属于自身的浮点数的值
	* @param sPropertyName:变量名; dValue:查询到的变量值
	* @return 0:成功查询; 1:不存在同名整形;
	*/
	int QueryProperty(string sPropertyName, double* dValue);
	/*
	* @brief 查询指定名称的属于自身的字符串的值
	* @param sPropertyName:变量名; sValue:查询到的变量值
	* @return 0:成功查询; 1:不存在同名整形;
	*/
	int QueryProperty(string sPropertyName, string* sValue);
};


#endif