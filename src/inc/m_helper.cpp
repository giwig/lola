/*
 * lua_helper.cpp
 *
 *  Created on: Apr 4, 2022
 *      Author: GiWiG
 */

#include "m_helper.hpp"

#include <iostream>

LuaHelper::LuaHelper()
{
	 luaL_openlibs(*L);
}

LuaHelper::~LuaHelper()
{
	lua_close(*L);
}

std::shared_ptr<lua_State*> LuaHelper::getShared_L()
{
	return L;
}

int LuaHelper::get_global_variable(const std::string in_var, std::string &out_var)
{
//	printf("LuaHelper::get_global_variable()\tUse count for L == %d\n\n", L.use_count());

	out_var = "nil";
	lua_getglobal(*L, in_var.c_str());
	if (lua_isnil(*L, -1) == false)
	{
		out_var = std::string(lua_tostring(*L, -1));
		return 1;
	}
	return 0;
}

int LuaHelper::call_global_function(const std::string in_var)
{
	lua_getglobal(*L, in_var.c_str());
	if (lua_isnil(*L, -1) == false)
	{
//		printf("============================= %s =========================================\n", in_var.c_str());
		if (lua_pcall(*L, 0, 0, 0))
		{
			return 0;
		}
		lua_pushnil(*L);
		lua_setglobal(*L, in_var.c_str());
		lua_pcall(*L, 1, 0, 0);
		return 1;
	}
	return 0;
}

int LuaHelper::get_global_array(const std::string in_var, std::vector<std::string> &out_var)
{
	out_var.clear();

	lua_getglobal(*L, in_var.c_str());
	if (lua_isnil(*L, -1)) 	return 0;
	lua_pushnil(*L);
	while (lua_next(*L, -2))
	{
		out_var.push_back(std::string(lua_tostring(*L, -1)));
		lua_pop(*L, 1);
	}
	return 1;
}

int LuaHelper::clear_global_variable(const std::string in_var)
{
	return luaL_dostring(*L, (in_var + " = nil").c_str());
}

