/*
 * lua_helper.cpp
 *
 *  Created on: Apr 4, 2022
 *      Author: GiWiG
 */

#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <lua.hpp>
#include <libiptc/libiptc.h>

#include "cpp_fs.hpp"
#include "m_helper.hpp"

using namespace std;

int lua_main(std::shared_ptr<lua_State*> L)
{
	/*
	std::shared_ptr<LuaHelper> p_helper(new LuaHelper(L));
	std::vector<string> mpac;

	p_helper->get_global_array("mpac", mpac);
	if (mpac.empty())
		return 0;

//	test_iptc();

	for (const std::string &value : mpac)
	{
		std::string str = "local t=require('" + value + "') return (t~=nil)";
		int reqRes = luaL_dostring(*L, str.c_str());
		if (reqRes == 0)
		{
			vector<string> urls;
			vector<string> sums;
			string src_dir;

			printf("PACKAGE: %s >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", value.c_str());
			std::vector<string> envs;
			p_helper->get_global_array("env", envs);
			for (string &env : envs)
			{
				char *e = getenv(env.c_str());
				printf("ENV: %s\n", env.c_str());
//				putenv((char *)env.c_str());
				setenv("LALA", env.c_str(), 1);
				setenv("LOLO", "This is LOLO", 1);
//				system(env.c_str());
			}

			std::string variable;
			p_helper->get_global_variable("pkgname", variable);
			printf(" * PKG: %s\n", variable.c_str());
//			int res = variable != "nil" ? printf("variable is == %s\n", variable.c_str()) : 0;

//			if (false == loc_call_global_function(L, "pkg_download"))
			if (false == p_helper->call_global_function("pkg_download"))
			{

				p_helper->get_global_variable("src_dir", src_dir);
				p_helper->get_global_array("pkgsource", urls);
				p_helper->get_global_array("sha256sums", sums);
				if (urls.capacity() > 0)
				{
					for (string pkg_url : urls)
					{

						auto index = distance(urls.begin(), find(urls.begin(), urls.end(), pkg_url));
						printf("%s\n", pkg_url.c_str());
						printf("%s\n", src_dir.c_str());
						printf("%s\n", fs_url_get_filename(pkg_url).c_str());
						std::string filename = (src_dir + "/" + fs_url_get_filename(pkg_url));
						string hash = fs_sha256sum_file(filename);
						if (false == fs_file_exists(filename) && sums[index] == hash)
						{
							char cBuf[8192] = { 0 };
							sprintf(cBuf, "wget %s -c -P %s", pkg_url.c_str(), src_dir.c_str());
							system(cBuf);
						}
						else
						{
							printf(" * file %s exists and hash %s is matched\n", filename.c_str(), hash.c_str());

						}

					}
				}
				printf(" * Download function not found! use internal:\n");

			}

			if (false == p_helper->call_global_function("pkg_extract"))
			{
				string tol_dir = "";
				p_helper->get_global_variable("tol_dir", tol_dir);
				printf(" * Extract function not found! use internal: %s\n", tol_dir.c_str());
			}

			p_helper->call_global_function("pkg_prepare");
			p_helper->call_global_function("pkg_build");
			p_helper->call_global_function("pkg_install");
			p_helper->call_global_function("pkg_package");

			printf("PACKAGE: %s <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", value.c_str());
			printf("\n\n\n\n");

		}
		else
		{
			printf("Can't load module %s\n", value.c_str());
			printf("Error: %s", lua_tostring(*L, -1));
		}
	}

	//*/
	return 1;
}
