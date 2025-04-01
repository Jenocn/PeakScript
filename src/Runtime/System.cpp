#include "system.h"

using namespace peak;

std::function<void(const std::string&)> System::_funcEcho = [](const std::string& msg) {
	std::cout << msg << std::endl;
};
std::function<std::string(const std::string&)> System::_funcOpenSrc = [](const std::string& filename) -> std::string {
	std::ifstream in(filename, std::ios::ate);
	if (!in.is_open()) {
		return "";
	}
	auto size { in.tellg() };
	if (size == 0) {
		return "";
	}
	in.seekg(0);
	std::string buffer;
	buffer.resize(static_cast<std::size_t>(size));
	in.read(buffer.data(), size);
	return buffer;
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
