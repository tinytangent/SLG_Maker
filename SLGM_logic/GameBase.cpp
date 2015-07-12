#include <string>
#include <map>
#include "GameBase.h"

using namespace std;

//////////////////////////////自身操作函数//////////////////////////////
/*
* @brief 新建指定名称的属于自身的整形并赋值
* @param sPropertyName:变量名; nValue:变量值
* @return 0:成功新建; 1:已存在同名整形; 2:已存在同名浮点数; 3:已存在同名字符串
*/
int GameBase::AddProperty(string sPropertyName, int nValue)
{
	if (nProperty.count(sPropertyName) == 1)
		return 1;
	if (dProperty.count(sPropertyName) == 1)
		return 2;
	if (sProperty.count(sPropertyName) == 1)
		return 3;
	nProperty[sPropertyName] = nValue;
	return 0;
}

/*
* @brief 新建指定名称的属于自身的整形并赋值
* @param sPropertyName:变量名; dValue:变量值
* @return 0:成功新建; 1:已存在同名整形; 2:已存在同名浮点数; 3:已存在同名字符串
*/
int GameBase::AddProperty(string sPropertyName, double dValue)
{
	if (nProperty.count(sPropertyName) == 1)
		return 1;
	if (dProperty.count(sPropertyName) == 1)
		return 2;
	if (sProperty.count(sPropertyName) == 1)
		return 3;
	dProperty[sPropertyName] = dValue;
	return 0;
}

/*
* @brief 新建指定名称的属于自身的整形并赋值
* @param sPropertyName:变量名;sValue:变量值
* @return 0:成功新建; 1:已存在同名整形; 2:已存在同名浮点数; 3:已存在同名字符串
*/
int GameBase::AddProperty(string sPropertyName, string sValue)
{
	if (nProperty.count(sPropertyName) == 1)
		return 1;
	if (dProperty.count(sPropertyName) == 1)
		return 2;
	if (sProperty.count(sPropertyName) == 1)
		return 3;
	sProperty[sPropertyName] = sValue;
	return 0;
}

/*
* @brief 删除指定名称的属于自身的变量
*        注意！就算在游戏过程中一个变量被删除了，它依然可能对游戏产生影响！
*        所以除非一局游戏彻底结束需要释放内存，否则尽量不要调用该函数！
* @param sPropertyName:变量名
* @return 0:成功删除; 1:不存在同名变量
*/
int GameBase::DeleteProperty(string sPropertyName)
{
	if (nProperty.count(sPropertyName) == 1)
	{
		nProperty.erase(sPropertyName);
		return 0;
	}
	if (dProperty.count(sPropertyName) == 1)
	{
		dProperty.erase(sPropertyName);
		return 0;
	}
	if (sProperty.count(sPropertyName) == 1)
	{
		sProperty.erase(sPropertyName);
		return 0;
	}
	return 1;
}

/*
* @brief 更改指定名称的属于自身的整形的值
* @param sPropertyName:变量名; nValue:变量值
* @return 0:成功新建; 1:不存在同名整形;
*/
int GameBase::ChangeProperty(string sPropertyName, int nValue)
{
	if (nProperty.count(sPropertyName) == 1)
		nProperty[sPropertyName] = nValue;
	else
		return 1;
	return 0;
}

/*
* @brief 更改指定名称的属于自身的浮点数的值
* @param sPropertyName:变量名; dValue:变量值
* @return 0:成功新建; 1:不存在同名整形;
*/
int GameBase::ChangeProperty(string sPropertyName, double dValue)
{
	if (dProperty.count(sPropertyName) == 1)
		dProperty[sPropertyName] = dValue;
	else
		return 1;
	return 0;
}

/*
* @brief 更改指定名称的属于自身的字符串的值
* @param sPropertyName:变量名; sValue:变量值
* @return 0:成功新建; 1:不存在同名整形;
*/
int GameBase::ChangeProperty(string sPropertyName, string sValue)
{
	if (sProperty.count(sPropertyName) == 1)
		sProperty[sPropertyName] = sValue;
	else
		return 1;
	return 0;
}

/*
* @brief 查询指定名称的属于自身的整形的值
* @param sPropertyName:变量名; nValue:查询到的变量值
* @return 0:成功查询; 1:不存在同名整形;
*/

//////////////////////////////查询函数//////////////////////////////
int GameBase::QueryProperty(string sPropertyName, int* nValue)
{
	if (nProperty.count(sPropertyName) == 0)
		return 0;
	*nValue = nProperty[sPropertyName];
	return 0;
}

/*
* @brief 查询指定名称的属于自身的浮点数的值
* @param sPropertyName:变量名; dValue:查询到的变量值
* @return 0:成功查询; 1:不存在同名整形;
*/
int GameBase::QueryProperty(string sPropertyName, double* dValue)
{
	if (dProperty.count(sPropertyName) == 0)
		return 0;
	*dValue = dProperty[sPropertyName];
	return 0;
}

/*
* @brief 查询指定名称的属于自身的字符串的值
* @param sPropertyName:变量名; sValue:查询到的变量值
* @return 0:成功查询; 1:不存在同名整形;
*/
int GameBase::QueryProperty(string sPropertyName, string* sValue)
{
	if (sProperty.count(sPropertyName) == 0)
		return 0;
	*sValue = sProperty[sPropertyName];
	return 0;
}