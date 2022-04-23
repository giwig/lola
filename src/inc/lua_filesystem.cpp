#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <lua.hpp>

#include "cpp_fs.hpp"


int lua_ls(lua_State *L)
{
	if(lua_gettop(L))
	{
		char buf[8192] = {0};
		char buf_command[8192] = {0};

		struct dirent *dir;
		DIR *d = opendir(lua_tostring(L, 1));
		if (d) {
			lua_newtable(L);
			int i = 1;
			while ((dir = readdir(d)) != NULL) {
				struct stat path_stat = {0};
				const auto fname = std::string(dir->d_name);
				stat(dir->d_name, &path_stat);
				if (S_ISREG(path_stat.st_mode) || S_ISDIR(path_stat.st_mode))
				{
					lua_pushnumber(L, i++);
					lua_pushstring(L, dir->d_name );
					lua_settable(L, -3);
				}
		    }
		    closedir(d);
		    return 1;
		}
	}
	return 0;
}

int lua_pwd(lua_State *L)
{
	if(lua_gettop(L) == 0)
	{
		char buf[8192] = {0};
		char buf_command[8192] = {0};

		getcwd(buf, 1024);
		lua_pushstring(L, buf);

	}
	return 1;
}



int lua_is_file(lua_State *L)
{
	if(lua_gettop(L))
	{
		struct stat path_stat = {0};
		stat(lua_tostring(L, 1), &path_stat);
		if ( S_ISREG(path_stat.st_mode) )
		{
			lua_pushboolean(L, true);
			return 1;
		}
	}
	lua_pushboolean(L, false);
	return 1;
}



int lua_url_get_filename(lua_State *L)
{
	if(lua_gettop(L))
	{
		std::string url = lua_tostring(L, 1);
//		std::string filename = strrchr( url.c_str(), '/' ) + 1;
		std::string filename = fs_get_filename_from_url(url.c_str());
		lua_pushstring(L, filename.c_str());
		return 1;
	}
	lua_pushstring(L, "Error");
	return 1;
}
