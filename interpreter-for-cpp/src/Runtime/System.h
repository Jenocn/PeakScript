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

public:
	static void Echo(const std::string& message);

private:
	static std::function<void(const std::string&)> _funcEcho;
};
} // namespace interpreter
} // namespace peak