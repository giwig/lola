/*
 * cpp_inet.hpp
 *
 *  Created on: Apr 6, 2022
 *      Author: giwig
 */

#ifndef SRC_INC_CPP_INET_HPP_
#define SRC_INC_CPP_INET_HPP_

#include <iostream>
#include <memory>
#include <string>


class InetTools {
private:
	InetTools();
	~InetTools();
public:
};

int inet_download_file(std::string, std::string, std::string );


#endif /* SRC_INC_CPP_INET_HPP_ */
