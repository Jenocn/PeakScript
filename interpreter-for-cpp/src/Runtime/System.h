/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <functional>

namespace peak::interpreter {
class System {
public:
	static void LocateEcho(std::function<void(const std::string&)> func);

public:
	static void Echo(const std::string& message);

private:
	static std::function<void(const std::string&)> _funcEcho;
};
} // namespace peak::interpreter