#include "System.h"
#include "Space.h"
#include "Value/ValueTool.h"
#include "Variable.h"

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

std::unordered_map<std::string, std::string> System::_usingToFilesMap;

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

bool System::AddUsingToFilename(const std::string& usingName, const std::string& filename) {
	if (_usingToFilesMap.find(usingName) == _usingToFilesMap.end()) {
		_usingToFilesMap.emplace(usingName, filename);
		return true;
	}
	return false;
}
const std::string& System::GetFilenameOfUsing(const std::string& usingName) {
	auto ite = _usingToFilesMap.find(usingName);
	if (ite != _usingToFilesMap.end()) {
		return ite->second;
	}
	static std::string EMPTY_STRING = "";
	return EMPTY_STRING;
}
