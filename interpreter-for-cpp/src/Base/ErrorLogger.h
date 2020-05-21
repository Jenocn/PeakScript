/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "CommonInclude.h"

namespace peak {
namespace interpreter {

enum class ErrorCode {
	None = 0,
	EndSign,
	SignSpace,
	Name,
	Bracket,
	ConstAssign,
	ForeachIn,
	String,
	Array,
};

class ErrorLogger {
public:
	static void Locate(std::function<void(const std::string&)> logger);
	static void ResetErrorCodeMap(const std::map<ErrorCode, std::string>& errorCodeMap);
	static void Log(const std::string& message);
	static void Log(ErrorCode code, const std::string& info);

private:
	static std::function<void(const std::string&)> _logger;
	static std::map<ErrorCode, std::string> _errorCodeMap;
};

} // namespace interpreter
} // namespace peak