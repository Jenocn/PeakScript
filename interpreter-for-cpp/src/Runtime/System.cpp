#include "System.h"

using namespace peak::interpreter;

std::function<void(const std::string&)> System::_funcEcho = [](const std::string& msg) {
	std::cout << msg << std::endl;
};
std::function<std::string(const std::string&)> System::_funcOpenSrc = [](const std::string& filename) -> std::string {
	std::ifstream in(filename);
	if (!in.is_open()) {
		return "";
	}
	std::stringstream buffer;
	buffer << in.rdbuf();
	in.close();
	return buffer.str();
};

void System::LocateEcho(std::function<void(const std::string&)> func) {
	_funcEcho = func;
}

void System::LocateOpenSrc(std::function<std::string(const std::string&)> func) {
	_funcOpenSrc = func;
}

void System::Echo(const std::string& message) {
	_funcEcho(message);
}

std::string System::OpenSrc(const std::string& filename) {
	return _funcOpenSrc(filename);
}
