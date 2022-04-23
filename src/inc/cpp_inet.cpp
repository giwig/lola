/*
 * cpp_inet.cpp
 *
 *  Created on: Apr 6, 2022
 *      Author: guest
 */

#include "cpp_fs.hpp"

#include "cpp_inet.hpp"


InetTools::InetTools()
{

}

InetTools::~InetTools()
{

}


int inet_download_file(std::string in_url, std::string in_dst_folder, std::string in_dst_filepath)
{
	if ( false == fs_file_exists(in_dst_filepath))
	{
		char cBuf[8192] = {0};
		printf("\t* File %s don't exists! Try to download it in %s\n", in_dst_filepath.c_str(), in_dst_folder.c_str());

		sprintf(cBuf, "wget -c -P %s/ %s ", in_dst_folder.c_str(), in_url.c_str()  );
//		printf("\t* CMD: %s\n", cBuf);
		system(cBuf);
	}

	if(false == fs_file_exists(in_dst_filepath)) {
		return false;
	}

	return true;
}


