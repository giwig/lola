#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <lua.hpp>

#include "lua_child_process.hpp"


int lua_bash_exec(lua_State *L)
{
	std::vector<std::string> vresult;
	std::string result = "";
	if(lua_gettop(L))
	{
//		printf("bash execute:\n");
		FILE *fp;
		char path[1035];
		char command[8192*4] = {0};

		sprintf(command, "%s", lua_tostring(L, 1));
		//*
		fp = popen(command, "r");
		while (fgets(path, sizeof(path), fp) != NULL) {
//		    printf("line: %s", path);
//		    result.append(path);
			vresult.push_back(path);
		}
		pclose(fp);
		result = std::accumulate(vresult.begin(), vresult.end(), std::string{});
		//*/
//		system(command);
	}
	lua_pushstring(L, result.c_str());
	return 1;
}

