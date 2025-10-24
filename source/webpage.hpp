#ifndef WEBPAGE_HPP
#define WEBPAGE_HPP

#include "crow.h"

#define ROOT_PREFIX "../"	// when ran from /build directory

crow::response loadWebpage(std::string path);
crow::response loadAsset(std::string path);

#endif
