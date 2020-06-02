/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Base/CommonInclude.h"

namespace peak {
namespace interpreter {

class Variable;

class System {
public:
	static void LocateEcho(std::function<void(const std::string&)> func);
	static void LocateOpenSrc(std::function<std::string(const std::string&)> func);

public:
	static void Echo(const std::string& message);
	static std::string OpenSrc(const std::string& filename);

public:
	static bool AddUsingToFilename(const std::string& usingName, const std::string& filename);
	static const std::string& GetFilenameOfUsing(const std::string& usingName);

private:
	static std::function<void(const std::string&)> _funcEcho;
	static std::function<std::string(const std::string&)> _funcOpenSrc;

private:
	static std::unordered_map<std::string, std::string> _usingToFilesMap;
};
} // namespace interpreter
} // namespace peak