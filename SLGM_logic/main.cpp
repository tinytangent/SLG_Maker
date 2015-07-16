#include "lua.hpp"
#include "LuaTools.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
/*	lua_State* LS;
	LS = luaL_newstate();
	static const luaL_Reg lualibs[] =
	{
		{ "base", luaopen_base },
		{ NULL, NULL}
	};

	const luaL_Reg *lib = lualibs;
	for(; lib->func != NULL; lib++)
	{
		lib->func(LS);
		lua_settop(LS, 0);
	}


	int bRet = luaL_loadfile(LS, "hello.lua");
	bRet = lua_pcall(LS,0,0,0);

	lua_getglobal(LS, "add");
	lua_pushnumber(LS, 50);
	lua_pushnumber(LS, 49);

	bRet = lua_pcall(LS, 2, 1, 0);

	std::string s = lua_tostring(LS, 1);
	std::cout << s << std::endl; 

	lua_pop(LS,1);

	lua_pushinteger(LS,3);
	lua_pushinteger(LS,2);
	lua_pushinteger(LS,1);
	lua_pushinteger(LS,0);

	

	int x = lua_tointeger(LS, 1);
	std::cout << x << std::endl;

	lua_close(LS);

	int a; std::cin>>a;*/

	LuaTools lt;
	lt.Load("hello.lua");

/*	lua_getglobal(lt.LS, "a");
	int a = lua_tonumber(lt.LS, -1);

	lua_getglobal(lt.LS, "b");
	string b = lua_tostring(lt.LS, -1);

	cout << a << b;*/
	
	lt.DumpGlobal();
	
	
	//lt.DumpGlobal();

	return 0;
}