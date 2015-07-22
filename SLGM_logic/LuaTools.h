#ifndef _LUA_TOOLS_H_
#define _LUA_TOOLS_H_

#include <string>
#include <iostream>

#include "lua.hpp"

using namespace std;

class LuaTools
{
public:
	lua_State *LS;

	~LuaTools();

public:
	void Load(string _LuaFileName);

	void DumpGlobal();
};






#endif;