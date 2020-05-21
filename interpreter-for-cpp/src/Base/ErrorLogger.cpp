#include "ErrorLogger.h"

using namespace peak::interpreter;

std::function<void(const std::string&)> ErrorLogger::_logger = [](const std::string& message) {
	std::cout << message << std::endl;
};

void ErrorLogger::Locate(std::function<void(const std::string&)> logger) {
	_logger = logger;
}

void ErrorLogger::Log(const std::string& message) {
	_logger("[!]error: " + message);
}

