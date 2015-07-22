#include "LuaTools.h"
void LuaTools::Load(string _LuaFileName)
{
	LS = luaL_newstate();
	int a = luaL_loadfile(LS, _LuaFileName.c_str());
	lua_pcall(LS,0,0,0);
	return;
}

void LuaTools::DumpGlobal()
{
	lua_pushglobaltable(LS);
	int nIndex = lua_gettop(LS);
	lua_pushnil(LS);
	while (lua_next(LS, nIndex))
	{
		bool flag = false;
		if (lua_istable(LS,-1))
		{
		}

		
		
		if (lua_isnumber(LS,-1))
		{
			cout << "number:" << lua_tostring(LS, -2) << "=" << lua_tonumber(LS, -1) << endl;
		}
		else
		{
			if (lua_isstring(LS,-1))
			{
				cout << "string:" << lua_tostring(LS, -2) << "=" << lua_tostring(LS, -1) << endl;
				flag = true;
			}
		}
		
		if (lua_isfunction(LS,-1))
		{
		}

		lua_pop(LS,1);
	}
	lua_pop(LS,1);
	return;
}

LuaTools::~LuaTools()
{
	delete LS;
}