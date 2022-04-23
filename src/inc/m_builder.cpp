/*
 * builder.cpp
 *
 *  Created on: Apr 4, 2022
 *      Author: GiWIG
 */

#include "m_builder.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>



LuaLinuxBuilder::LuaLinuxBuilder() : LpacFile()
{
	L = getShared_L();
}
LuaLinuxBuilder::~LuaLinuxBuilder()
{
}

void LuaLinuxBuilder::OptionsAdd(char *in_opt)
{
	options.push_back(in_opt);
}

void LuaLinuxBuilder::OptionsPrint()
{
	int opt = 0;
	extern int opterr;

	printf("\n\n(L)ua (L)inux Builder:\n\n");

	opterr = 0;
	while ((opt = getopt(options.size(), &options[0], "hv")) != -1)
	{
		switch (opt)
		{
		case 'v':
			printf(" * %s\n", LUA_VERSION);
			printf(" * %s v%s\n", &options[0][2], "0.0.1");
			printf("\n\n\n");
			return;
		case 'h':
			printf("Usage: %s [flags optional] [path to build scripts]\n", options[0]);
			printf("\n\tHELP:\n");
			printf("\t=====================================================\n");
			printf("\t-h\t\t\tthis help\n");
			printf("\t-v\t\t\tversion for %s\n", options[0]);
			printf("\n\tFLAGS:\n");
			printf("\t=====================================================\n");
			printf("\t-b [path to *.lpac]\tFile LPAC with configuration for system build\n");
			printf("\n\n\n");
			return;
		default:
			break;
		}
	}

//	printf("\033c");
	opt = 0;
	optind = 0;

	while ((opt = getopt(options.size(), &options[0], "b:h")) != -1)
	{
		switch (opt)
		{
		case 'b':
			if (optind >= options.size() )
			{
				printf("Build directory is %s\n", options[optind - 1]);
				char cPath[8192] = { 0 };

				sprintf(cPath, "%s", options[optind - 1]);
				printf("Dofile: %s\n\n", cPath);
				LuaFilename = cPath;

				luaL_dostring(*L, "package.path = 'lua/?.lua;'");
//				luaL_dostring(*L, "package.path = 'lua/base/?.lua;'..package.path ");
//				luaL_dostring(*L, "package.path = 'lua/toolchain/?.lua;'..package.path ");

				(luaL_loadfile(*L, cPath) || lua_pcall(*L, 0, LUA_MULTRET, 0));


				std::string var = "";
//				if ( get_global_variable("src_dir", var) )	printf("%s\n", var.c_str());
//				if ( get_global_variable("tol_dir", var) )	printf("%s\n", var.c_str());

				package_looper();
			}
			break;
		default:
			break;
		}
	}

}



