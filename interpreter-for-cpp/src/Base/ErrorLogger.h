/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "CommonInclude.h"

namespace peak {
namespace interpreter {

class ErrorLogger {
public:
	static void Locate(std::function<void(const std::string&)> logger);
	static void Log(const std::string& message);

private:
	static std::function<void(const std::string&)> _logger;
};

} // namespace interpreter
} // namespace peak