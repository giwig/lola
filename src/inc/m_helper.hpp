/*
 * lua_helper.hpp
 *
 *  Created on: Apr 4, 2022
 *      Author: GiWiG
 */

#ifndef SRC_CPP_LUA_LUA_HELPER_HPP_
#define SRC_CPP_LUA_LUA_HELPER_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <vector>
#include <lua.hpp>

class LuaHelper
{
private:
public:
	std::shared_ptr<lua_State*> L = std::make_shared<lua_State*>( luaL_newstate() );

	LuaHelper();
	~LuaHelper();


	std::shared_ptr<lua_State*> getShared_L();

	int get_global_variable		(const std::string , std::string &);
	int call_global_function	(const std::string );
	int get_global_array		(const std::string , std::vector<std::string> &);
	int clear_global_variable	(const std::string );
};

#endif /* SRC_CPP_LUA_LUA_HELPER_HPP_ */
