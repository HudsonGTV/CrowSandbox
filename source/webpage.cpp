#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

#include "webpage.hpp"
#include "response_codes.hpp"

/**
 * Local variables / functions
**/

const std::unordered_map<std::string, std::string> headerFileTypes = {
	{".html", 	"text/html; charset=UTF-8"},
	{".css", 	"text/css"},
	{".js", 	"application/javascript"},
	{".png", 	"image/png"},
	{".jpg", 	"image/jpeg"},
	{".jpeg", 	"image/jpeg"},
	{".gif", 	"image/gif"},
	{".svg", 	"image/svg+xml"},
	{".pdf", 	"application/pdf"},
	{".json", 	"application/json"},
};

/**
 * Safe function for reading a file meant to be sent to client
 * Returns nothing if unsafe, or 404 if file not able to be opened (not found)
 */
std::string readFileClientSafe(std::string path) {

	// Guard against dangerous paths
	if(path.find("..") != std::string::npos)
		return "";

	// Open file for reading
	std::ifstream fileIn(std::string(ROOT_PREFIX) + path);

	// If file cant be opened, return 404
	if(!fileIn) return "404";

	// File good
	std::stringstream buff;
	buff << fileIn.rdbuf();

	fileIn.close();

	return buff.str();

}

/**
 * Returns a file paths extension or "" if no extension found
 */
std::string getFileExtension(std::string path) {
	size_t extPos = path.rfind(".");
	if(extPos == std::string::npos)
		return "";	// no file extension found
	return path.substr(extPos);
}

/**
 * Header-defined functions
**/

/**
 * Will load a webpage for use as a response
 * @param path - the file path
 */
crow::response loadWebpage(std::string path) {

	// Ensure not accessing resources it shouldn't
	if(path.find("..") != std::string::npos)
		return crow::response(ResponseCode::FORBIDDEN, "../ not allowed");

	std::string fileContents = readFileClientSafe("web/" + path + ".html");

	// Check if the file doesnt exist
	if(fileContents == "404")
		return crow::response(
			ResponseCode::NOT_FOUND,
			"text/html; charset=UTF-8",
			"Page not found"
		);

	//return res;
	return crow::response(
		ResponseCode::OK,
		"text/html; charset=UTF-8",
		fileContents
	);

}

/**
 * Loads an asset if it is a valid file type
 * @param path - the file path
 */
crow::response loadAsset(std::string path) {

	/* Guard against dangerous file types */
	std::string fileExt = getFileExtension(path);

	auto it = headerFileTypes.find(fileExt);
	// Do not allow loading files not whitelisted in map (may update this later)
	if(it == headerFileTypes.end())
		return crow::response(ResponseCode::FORBIDDEN);

	/* Read in file */
	std::string fileContents = readFileClientSafe("assets/" + path);

	// If file wasnt found return error
	if(fileContents == "404")
		return crow::response(
			ResponseCode::NOT_FOUND,
			"text/html; charset=UTF-8",
			"Asset not found"
		);

	return crow::response(
		ResponseCode::OK,
		it->second,
		fileContents
	);
}
