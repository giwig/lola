/*
 * cpp_inet.hpp
 *
 *  Created on: Apr 6, 2022
 *      Author: giwig
 */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "cpp_fs.hpp"


std::string fs_get_filename_from_url(std::string url)
{
	return strrchr( url.c_str(), '/' ) + 1;
}


bool fs_file_exists(std::string filename)
{
	if( access( filename.c_str(), F_OK ) == 0 ) {
	    return true;
	} else {
	    return false;
	}
}

std::string fs_get_file_sha256sum(std::string filename)
{
	FILE *file;

	char command[8192] = {0};

	file = fopen(filename.c_str(), "r");
	std::string hash = calculateHash(file);
	fclose(file);
	return hash;
}

std::string fs_get_dir_from_archive	(std::string in_archive)
{
	char cCmd[8192]  = {0};
	sprintf(cCmd, "tar tf %s | sed -e 's@/.*@@' | uniq", in_archive.c_str());

    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cCmd, "r");
    if (!pipe) return "";
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        return "";
    }
    pclose(pipe);
    return result;
}

bool fs_file_is_compressed(std::string in_file)
{
	char cCmd[8192]  = {0};
	sprintf(cCmd, "file %s | grep -i compressed", in_file.c_str());

    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cCmd, "r");
    if (!pipe) return false;
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        return false;
    }
    pclose(pipe);
    if( result.find("compressed") != std::string::npos )
    	return true;

	return false;
}


bool fs_file_check_sha256sum(std::string& in_src, std::string in_hash)
{
	if( false == fs_file_exists(in_src))
	{
		return false;
	}

	std::string hash = fs_get_file_sha256sum(in_src);
	if( hash != in_hash )
	{
		in_src = hash;
		return false;
	}

	return true;
}


bool fs_extract_archive(std::string in_src_file, std::string in_dst_path  )
{
	if( false == fs_file_exists(in_src_file) )
		return false;

	char cBuf[8192] = {0};

	sprintf(cBuf, "tar -xf %s -C%s", in_src_file.c_str(), in_dst_path.c_str());
	system(cBuf);

	return true;
}


bool fs_path_exists(std::string in_path)
{
	DIR* dir = opendir(in_path.c_str());
	if (dir) {
	    /* Directory exists. */
	    closedir(dir);
	    return true;
	} else if (ENOENT == errno) {
	    /* Directory does not exist. */
	} else {
	    /* opendir() failed for some other reason. */
	}
	return false;
}

bool fs_mkdir(std::string in_path)
{
//	char cBuf[8192] = {0};

//	sprintf(cBuf, "mkdir -pv %s", in_path.c_str());
//	system(cBuf);
	if ( 0 == mkdir(in_path.c_str(), 0777))
		return true;
	return false;
}


bool fs_chdir(std::string in_dir)
{
	if( 0 != chdir(in_dir.c_str()))
	{
		return false;
	}
	return true;
}



