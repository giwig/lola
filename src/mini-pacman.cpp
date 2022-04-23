/*
 * lua_helper.cpp
 *
 *  Created on: Apr 4, 2022
 *      Author: GiWiG
 */

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

#include "inc/m_builder.hpp"

using namespace std;

/*
std::string calculateHash(FILE *file);
int lua_ls(lua_State *L);
int lua_pwd(lua_State *L);
int lua_is_file(lua_State *L);
int lua_url_get_filename(lua_State *L);
int lua_main(lua_State* L);

void init_envs(lua_State *L);
//*/

/*
int lua_bash_exec(lua_State *L)
{
	if(lua_gettop(L))
	{
//		printf("bash execute:\n");
		FILE *fp;
		char path[1035];
		char command[8192] = {0};

		sprintf(command, "%s", lua_tostring(L, 1));

		fp = popen(command, "r");
		while (fgets(path, sizeof(path), fp) != NULL) {
		    printf("line: %s", path);
		}
		pclose(fp);

		system(command);
	}
	return 0;
}

int lua_sha256sum_file(lua_State *L)
{
	if(lua_gettop(L))
	{
		FILE *file;

		char command[8192] = {0};
		sprintf(command, "%s", lua_tostring(L, 1));

		file = fopen(command, "r");
		std::string hash = calculateHash(file);
		fclose(file);
		lua_pushstring(L, hash.c_str());
		return 1;
	}
	lua_pushstring(L, "");
	return 1;
}

int lua_chroot(lua_State *L)
{
	if(lua_gettop(L))
	{
		char buf[8192] = {0};
		char buf_command[8192] = {0};
//		getcwd(buf, 1024);
//		printf("current working directory: %s\n", buf);

		sprintf(buf_command, "%s", lua_tostring(L, 1));
		chdir(buf_command);
		if( -1 == chroot(buf_command))
		{
			perror("chroot");
			printf("Have you tried running this as root?\n");
		}
//		getcwd(buf, 1024);
//		printf("current working directory: %s\n", buf);

	}
	return 0;
}
//*/



int main(int argc, char **argv)
{

	LuaLinuxBuilder* llb = new LuaLinuxBuilder();
	for (int i = 0; i < argc; i++ )
	{
		llb->OptionsAdd(argv[i]);
	}

	llb->OptionsPrint();

	return 0;

	/*
	lua_State* L = luaL_newstate();

	lua_register(L, "cpp_bash", lua_bash_exec);
	lua_register(L, "cpp_sha256file", lua_sha256sum_file);
	lua_register(L, "cpp_chroot", lua_chroot);
	lua_register(L, "cpp_ls", lua_ls);
	lua_register(L, "cpp_pwd", lua_pwd);
	lua_register(L, "cpp_is_file", lua_is_file);
	lua_register(L, "cpp_url_get_filename", lua_url_get_filename);

	init_envs(L);

	luaL_openlibs(L);

    luaL_dostring(L, "package.path = 'lua/?.lua;'");
    luaL_dostring(L, "package.path = 'lua/base/?.lua;'..package.path ");
    luaL_dostring(L, "package.path = 'lua/toolchain/?.lua;'..package.path ");

	if(luaL_dofile(L, "lua/test.lua"))
	{
		printf("Error: %s", lua_tostring(L,-1));
	}
    lua_main(L);

	lua_close(L);
	//*/

	return 0;
}
