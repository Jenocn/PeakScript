/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "base/error_logger.h"

namespace peak {

class System {
public:
	static void LocateEcho(std::function<void(const std::string&)> func);
	static void LocateOpenSrc(std::function<std::string(const std::string&)> func);

public:
	static void Echo(const std::string& message);
	static const std::string& OpenSrc(const std::string& filename, std::string& outAbsPath);
	static void AddSearchDir(const std::string& dir);

private:
	static std::function<void(const std::string&)> _funcEcho;
	static std::function<std::string(const std::string&)> _funcOpenSrc;
	static std::unordered_set<std::string> _searchPathList;
	static std::unordered_map<std::string, std::string> _abspathToSrcMap;
};
} // namespace peak