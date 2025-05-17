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
std::unordered_set<std::string> System::_searchPathList;
std::unordered_map<std::string, std::string> System::_abspathToSrcMap;

void System::LocateEcho(std::function<void(const std::string&)> func) {
	_funcEcho = func;
}

void System::LocateOpenSrc(std::function<std::string(const std::string&)> func) {
	_funcOpenSrc = func;
}

void System::Echo(const std::string& message) {
	_funcEcho(message);
}

const std::string& System::OpenSrc(const std::string& filename, std::string& outAbsPath) {
	auto absPath = std::filesystem::absolute(filename).string();
	if (auto ite = _abspathToSrcMap.find(absPath); ite != _abspathToSrcMap.end()) {
		outAbsPath = ite->first;
		return ite->second;
	}
	if (std::filesystem::exists(absPath)) {
		auto src = _funcOpenSrc(absPath);
		outAbsPath = absPath;
		_abspathToSrcMap.emplace(absPath, std::move(src));
		return _abspathToSrcMap[absPath];
	}
	for (auto& path : _searchPathList) {
		auto target = std::filesystem::path(path) / filename;
		absPath = std::move(std::filesystem::absolute(target.lexically_normal()).string());
		if (auto ite = _abspathToSrcMap.find(absPath); ite != _abspathToSrcMap.end()) {
			outAbsPath = ite->first;
			return ite->second;
		}
		if (!std::filesystem::exists(absPath)) {
			continue;
		}
		auto src = _funcOpenSrc(absPath);
		outAbsPath = absPath;
		_abspathToSrcMap.emplace(absPath, std::move(src));
		return _abspathToSrcMap[absPath];
	}
	static std::string DEF;
	return DEF;
}

void System::AddSearchDir(const std::string& dir) {
	_searchPathList.emplace(dir);
}
