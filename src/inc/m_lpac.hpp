/*
 * lpac.hpp
 *
 *  Created on: Apr 4, 2022
 *      Author: GiWiG
 */

#ifndef SRC_CPP_LPAC_LPAC_HPP_
#define SRC_CPP_LPAC_LPAC_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <lua.hpp>
#include "m_helper.hpp"
#include "cpp_fs.hpp"

typedef struct s_lpac
{
	// Global variables
	std::string 				src_dir;
	std::string 				tol_dir;

	// Package variables
	std::string 				pkg_name;
	std::string 				pkg_version;
	std::string 				pkg_release;
	std::vector<std::string> 	pkg_sources;
	std::vector<std::string> 	pkg_files;
	std::vector<std::string> 	pkg_sha256sums;
	std::vector<std::string> 	pkg_sha512sums;
	std::vector<std::string> 	pkg_md5sums;

	std::vector<std::string> 	global_envs;

	s_lpac()
	{
		clear();
	}

	~s_lpac()
	{
		clear();
	}

	void clear()
	{
		src_dir		= "";
		tol_dir		= "";

		pkg_name 	= "";
		pkg_version = "";
		pkg_release = "";
		pkg_sources.clear();
		pkg_files.clear();
		pkg_sha256sums.clear();
		pkg_sha512sums.clear();
		pkg_md5sums.clear();
		global_envs.clear();
	};

	void sources_to_files()
	{
		pkg_files.clear();
		for( std::string file : pkg_sources)
		{
			pkg_files.push_back(fs_get_filename_from_url(file));
		}
	};

	std::string getSourceDirRoot()
	{
		return src_dir;
	}
	std::string getBuildDirRoot()
	{
		return tol_dir;
	}

	std::string getBuildDir()
	{
		std::string build_dir = tol_dir + "/" + fs_get_dir_from_archive(getFileInSourceDirById(0).c_str());
		build_dir.erase(std::remove(build_dir.begin(), build_dir.end(), '\n'), build_dir.end() );
		return build_dir;
 	}

	std::string getFileInSourceDirById(int _id)
	{
		return _id >= pkg_files.size() 			? "" : src_dir + "/" + pkg_files.at(_id);
	}
	std::string getDestDirInBuildDirById(int _id)
	{
		return _id >= pkg_files.size() 			? "" : tol_dir + "/" + pkg_files.at(_id);
	}

	std::string getFileById(int _id)
	{
		return _id >= pkg_files.size() 			? "" : pkg_files.at(_id);
	}
	std::string getSourceById(int _id)
	{
		return _id >= pkg_sources.size() 		? "" : pkg_sources.at(_id);
	}
	std::string getSha256ById(int _id)
	{
		return _id >= pkg_sha256sums.size() 	? "" : pkg_sha256sums.at(_id);
	}
	std::string getSha512ById(int _id)
	{
		return _id >= pkg_sha512sums.size() 	? "" : pkg_sha512sums.at(_id);
	}
	std::string getMD5ById(int _id)
	{
		return _id >= pkg_md5sums.size() 		? "" : pkg_md5sums.at(_id);
	}

} S_LPAC;

class LpacFile : public LuaHelper
{
private:
	std::shared_ptr<lua_State*> L;
	std::shared_ptr<S_LPAC> 	LpacData = std::make_shared<S_LPAC>( s_lpac() );

public:
	LpacFile();
	~LpacFile();

	void						FillPkgData();

	std::shared_ptr<s_lpac> 	getLpacData();

	std::string 				getPkgName();
	std::string 				getPkgVersion();
	std::string 				getPkgRelease();
	std::vector<std::string>	getPkgSource();
	std::vector<std::string>	getPkgSha256Sums();
	std::vector<std::string>	getPkgSha512Sums();
	std::vector<std::string>	getPkgMD5Sums();

	void	clear_lpac_variables();
	void	package_looper();
	bool	pkg_clean();
	bool	pkg_download();
	bool	pkg_extract();

	void 	pkg_set_global_envs();

	std::vector<std::string> split (std::string s, std::string delimiter);

//	int test_iptc();
};

#endif /* SRC_CPP_LPAC_LPAC_HPP_ */
