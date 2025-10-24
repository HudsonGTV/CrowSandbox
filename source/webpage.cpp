#include <string>
#include <fstream>

#include "webpage.hpp"



crow::response loadWebpage(std::string path) {

	// Response to return (empty for now)
	crow::response res;

	// Ensure not accessing resources it shouldn't
	if(path.find("..") != std::string::npos) return crow::response(401, "Access denied.");

	// Open file for reading
	std::ifstream fileIn(std::string(ROOT_PREFIX) + "web/" + path + ".html");

	if(!fileIn) {
		// If file cant be opened, give 404 error and set response data
		return crow::response(404, "Page not found");
	} else {
		// File good
		std::stringstream buff;
		buff << fileIn.rdbuf();
		//res.code = 200;
		//res.body = buff.str();
		res = crow::response(200, buff.str());
	}

	fileIn.close();

	return res;
}

//TODO: PREVENT LOADING CERTAIN FILE EXTENSIONS LIKE .CPP
crow::response loadAsset(std::string path) {
	crow::response res;

	// Ensure not accessing resources it shouldn't
	if(path.find("..") != std::string::npos) return crow::response(401, "Access denied.");

	

	return crow::response(path);
}
