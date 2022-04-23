/*
 * lua_helper.cpp
 *
 *  Created on: Apr 4, 2022
 *      Author: GiWiG
 */

#include "m_lpac.hpp"

#include "cpp_inet.hpp"
#include "lua_child_process.hpp"
#include "lua_envs.hpp"

LpacFile::LpacFile() : LuaHelper()
{
	L = getShared_L();
	lua_register(*L, "cpp_bash", lua_bash_exec);
	init_envs(*L);

}

LpacFile::~LpacFile(){

}

std::shared_ptr<s_lpac> LpacFile::getLpacData()
{
	return LpacData;
}

std::string LpacFile::getPkgName()
{
	return LpacData->pkg_name;
}

std::string LpacFile::getPkgVersion()
{
	return LpacData->pkg_version;
}

std::string LpacFile::getPkgRelease()
{
	return LpacData->pkg_release;
}
std::vector<std::string> LpacFile::getPkgSource()
{
	return LpacData->pkg_sources;
}
std::vector<std::string> LpacFile::getPkgSha256Sums()
{
	return LpacData->pkg_sha256sums;
}
std::vector<std::string> LpacFile::getPkgSha512Sums()
{
	return LpacData->pkg_sha512sums;
}
std::vector<std::string> LpacFile::getPkgMD5Sums()
{
	return LpacData->pkg_md5sums;
}

std::vector<std::string> LpacFile::split (std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

/*
 int LpacFile::test_iptc()
 {
 const char *chain = NULL;
 const char *tablename = "filter";
 struct xtc_handle *h = iptc_init(tablename);

 if (!h)
 {
 h = iptc_init(tablename);
 printf("Error initializing: %s\n", iptc_strerror(errno));
 return -1;
 }

 for (chain = iptc_first_chain(h); chain; chain = iptc_next_chain(h))
 {
 printf("%s\n", chain);
 }
 return 0;
 }
 //*/

void LpacFile::clear_lpac_variables()
{
	clear_global_variable("pkgname");
	clear_global_variable("pkgver");
	clear_global_variable("pkgrel");
	clear_global_variable("pkgsource");
	clear_global_variable("sha256");
	clear_global_variable("sha512");
	clear_global_variable("md5sums");

	clear_global_variable("pkg_download");
	clear_global_variable("pkg_extract");
	clear_global_variable("pkg_prepare");
	clear_global_variable("pkg_build");
	clear_global_variable("pkg_install");
	clear_global_variable("pkg_package");

	clear_global_variable("env_global");
}

void LpacFile::FillPkgData()
{
	LpacData->clear();

	get_global_variable("src_dir", 		LpacData->src_dir 		);
	get_global_variable("tol_dir", 		LpacData->tol_dir 		);

	get_global_variable("pkgname", 		LpacData->pkg_name 		);
	get_global_variable("pkgver", 		LpacData->pkg_version 	);
	get_global_variable("pkgrel", 		LpacData->pkg_release 	);

	get_global_array(	"pkgsource",	LpacData->pkg_sources	);
	get_global_array(	"sha256sums", 	LpacData->pkg_sha256sums);
	get_global_array(	"sha512sums", 	LpacData->pkg_sha512sums);
	get_global_array(	"md5sums", 		LpacData->pkg_md5sums);

	get_global_array(	"env_global", 	LpacData->global_envs);
	LpacData->sources_to_files();

}

bool LpacFile::pkg_clean()
{
	printf(" * Intern clean function\n");

	std::string dst_dir = LpacData->getBuildDir();
//	printf("\t%s\n", LpacData->getFileById(0).c_str());
//	printf("\t%s\n", LpacData->getFileInSourceDirById(0).c_str());
	printf("\t%s\n", dst_dir.c_str());
	if( true == fs_path_exists(dst_dir) )
	{
		printf("\t* Build Dir Root == %s\n", LpacData->getBuildDirRoot().c_str() );
		printf("\t* Build Dir 	  == %s\n", LpacData->getBuildDir().c_str() );
		char cBuf[8192] = {0};
		sprintf(cBuf, "sudo rm -r %s", dst_dir.c_str());
		printf("\t%s\n", cBuf );
		system(cBuf);
	}
	return true;
}

bool LpacFile::pkg_download()
{
	printf("\n\n * Intern download function\n\n");

	// for PKGSOURCE array []
	for(int i = 0; i < LpacData->pkg_files.capacity(); i++)
	{
		std::string filename 	= LpacData->getFileInSourceDirById(i);
		std::string src_dir 	= LpacData->getSourceDirRoot();
		std::string url 		= LpacData->getSourceById(i);
		// check if file exists
		if(false == inet_download_file( url, src_dir, filename))
		{
			printf("\t* Something wrong with download");
			return false;
		}

		// Check HASH for file
		std::string hash_lpac = LpacData->getSha256ById(i);
		if( false == fs_file_check_sha256sum(filename, hash_lpac ))
		{
			printf("\t* File hash dosn't match lpac[%s] file[%s]\n", hash_lpac.c_str(), filename.c_str() );
			return false;
		}

		printf("\n\n");
	}

	return true;
}

bool LpacFile::pkg_extract()
{
	printf("\n\n * Intern extract function\n");
	std::string dst_dir = LpacData->tol_dir;
	for( std::string file: LpacData->pkg_files)
	{
		std::string dst_file = LpacData->src_dir + "/" + file;
		if( true == fs_file_is_compressed(dst_file))
		{
			if ( false == fs_path_exists(dst_dir) )
			{
				if (false == fs_mkdir(dst_dir) )
					return false;
			}
			printf("\t* File %s is compressed. Extract it to %s\n", ( LpacData->src_dir + "/" + file).c_str(), dst_dir.c_str());
			fs_extract_archive(dst_file, LpacData->tol_dir);
		}
	}
	return true;
}


void LpacFile::pkg_set_global_envs()
{
	for( std::string& genv: LpacData->global_envs)
	{
		std::vector<std::string> result = split(genv,  "=");
		printf("genv == %s && %s\n", result[0].c_str(), result[1].c_str());
		setenv(result[0].c_str(), result[1].c_str(), 1);
	}
}


void LpacFile::package_looper()
{
	std::vector<std::string> lpacs;
	if ( get_global_array("lpacs", lpacs) )
	{
		for( std::string& lpac: lpacs)
		{
			printf("%s\n", lpac.c_str());
			std::string str = "local t=require('" + lpac + "') return (t~=nil)";
			if( luaL_dostring(*L, str.c_str()) == 0)
			{
				FillPkgData();
				pkg_set_global_envs();

				printf(" * Package Name == %s\n", getPkgName().c_str() );
				printf(" * Package Name == %s\n", getPkgVersion().c_str() );

				if( false == call_global_function("pkg_clean"))
				{
					pkg_clean();
				}

				if( false == call_global_function("pkg_download"))
				{
					if( false == pkg_download())
					{
						printf("While downloading package '%s' occurs some errors\n\n", getPkgName().c_str());
						break;
					}
				}

				if( false == call_global_function("pkg_extract"))
				{
					if( false == pkg_extract())
					{
						printf("Can't extract package %s\n\n", getPkgName().c_str());
						break;
					}
				}

				fs_chdir(LpacData->getBuildDir());
				call_global_function("pkg_prepare");

				fs_chdir(LpacData->getBuildDir());
				call_global_function("pkg_build");

				fs_chdir(LpacData->getBuildDir());
				call_global_function("pkg_install");

				fs_chdir(LpacData->getBuildDir());
				call_global_function("pkg_package");

				if( false == call_global_function("pkg_clean"))
				{
					pkg_clean();
				}

				clear_lpac_variables();

			}
		}
	}
}

