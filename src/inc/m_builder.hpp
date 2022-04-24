/*
 * builder.hpp
 *
 *  Created on: Apr 4, 2022
 *      Author: giwig
 */

#ifndef SRC_BUILDER_BUILDER_HPP_
#define SRC_BUILDER_BUILDER_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <lua.hpp>
#include "m_lpac.hpp"
#include "lua_child_process.hpp"


class LuaLinuxBuilder : public LpacFile
{
private:
	std::shared_ptr<lua_State*> L;

	std::vector<char*> options;

	std::string LuaFilename = "";
public:

	LuaLinuxBuilder();
	~LuaLinuxBuilder();

	void OptionsAdd(char* );
	void OptionsPrint();
};

#endif /* SRC_BUILDER_BUILDER_HPP_ */


