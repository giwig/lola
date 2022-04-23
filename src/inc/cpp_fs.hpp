#ifndef SRC_CPP_FS_FS_HPP_
#define SRC_CPP_FS_FS_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <cstring>
//#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <dirent.h>

//class Fs {
//private:
//public:
//};


	std::string calculateHash(FILE *file);

	std::string fs_get_filename_from_url	(std::string );
	bool 		fs_file_exists				(std::string );
	std::string fs_get_file_sha256sum		(std::string );
	std::string fs_get_dir_from_archive		(std::string );
	bool 		fs_file_is_compressed		(std::string );
	bool		fs_file_check_sha256sum		(std::string&, std::string );
	bool 		fs_extract_archive			(std::string, std::string );
	bool 		fs_path_exists				(std::string );
	bool 		fs_mkdir					(std::string );
	bool 		fs_chdir					(std::string );

#endif
