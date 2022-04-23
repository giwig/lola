#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <lua.hpp>

using namespace std;


int lua_get_env(lua_State *L)
{
	if(lua_gettop(L))
	{
		std::string v_env = std::string( lua_tostring(L, 1) );
		v_env = std::string( getenv(v_env.c_str()) );
		v_env.empty() ? lua_pushnil(L) : lua_pushstring(L, v_env.c_str() );
		return 1;
	}
	lua_pushnumber(L, 999);
	return 1;
}


int lua_set_env(lua_State *L)
{
	if(lua_gettop(L) == 3)
	{
		std::string v_name  	= std::string( lua_tostring(L, 1) );
		std::string v_value 	= std::string( lua_tostring(L, 2) );
		int 		v_replace 	= lua_tonumber(L, 3);
		int 		v_resolve	= lua_isnil(L, 4) ? 0 : 1;
		if(v_resolve)
		{
			printf("DEBUG: Resolve ENV variable\n");
		}
		lua_pushnumber(L, setenv(v_name.c_str(), v_value.c_str(), v_replace));
		return 1;
	}
	lua_pushnumber(L, 999);
	return 1;
}


int lua_del_env(lua_State *L)
{
	if(lua_gettop(L))
	{
		std::string v_name  	= std::string( lua_tostring(L, 1) );
		lua_pushnumber(L, unsetenv(v_name.c_str()));
		return 1;
	}
	lua_pushnumber(L, 999);
	return 1;
}

int lua_clear_env(lua_State *L)
{
	lua_pushnumber(L, clearenv());
	return 1;
}


void init_envs(lua_State *L)
{
	lua_register(L, "cpp_get_env", lua_get_env);
	lua_register(L, "cpp_set_env", lua_set_env);
	lua_register(L, "cpp_del_env", lua_del_env);
	lua_register(L, "cpp_clear_env", lua_clear_env);
}



