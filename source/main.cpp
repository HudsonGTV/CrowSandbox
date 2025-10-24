#include "crow.h"
#include "webpage.hpp"

int main() {

	crow::SimpleApp app;

	/**
	 * API Calls here
	 */

	// Basic addition test
	CROW_ROUTE(app, "/api/<int>/<int>")([](int i1, int i2) {
		return crow::response("{\"answer\": \"" + std::to_string(i1 + i2) + "\"}");
	});

	// Generic API catch
	CROW_ROUTE(app, "/api/<path>")([](std::string path) {
		return crow::response(R"({"message": "ok"})");
	});

	/**
	 * Webpage/asset calls here
	 */

	// Allow assets to be fetched from server
	CROW_ROUTE(app, "/assets/<path>")([](std::string path) {
		return loadAsset(path);
	});

	// serve general webpages
	CROW_ROUTE(app, "/<path>")([](std::string path) {
		//return std::string("<p>Hello, Crow!</p><p>Path: ") + path + "</p>";
		return loadWebpage(path);
	});
	
	CROW_ROUTE(app, "/")([]() {
		return loadWebpage("index");
	});

	app.port(80).multithreaded().run();

}