/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Base/CommonInclude.h"

namespace peak {
namespace interpreter {

class System {
public:
	static void LocateEcho(std::function<void(const std::string&)> func);
	static void LocateOpenSrc(std::function<std::string(const std::string&)> func);

public:
	static void Echo(const std::string& message);
	static std::string OpenSrc(const std::string& filename);

private:
	static std::function<void(const std::string&)> _funcEcho;
	static std::function<std::string(const std::string&)> _funcOpenSrc;
};
} // namespace interpreter
} // namespace peak