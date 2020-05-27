/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "CommonInclude.h"

namespace peak {
namespace interpreter {

enum class ErrorRuntimeCode {
	None = 0,
	Space,
	Variable,
	Block,
	Condition,
	DoWhile,
	Echo,
	Expression,
	ExpressionDouble,
	FunctionCall,
	Math,
	ExpressionNot,
	SelfAssign,
	Array,
	ExpressionVariable,
	For,
	Foreach,
	FunctionDefine,
	Loop,
	Return,
	TryCatchFinally,
	VariableAssign,
	VariableDefine,
	VariableSet,
	While,
	VariableNameAnalysis,
	VariableArrayItemAnalysis,
	New,
	ObjectDefine,
};

class ErrorLogger {
public:
	static void Locate(std::function<void(const std::string&)> logger);
	static void Log(const std::string& message);
	static void LogParseError(const std::string& src, std::size_t size, std::size_t pos);
	static void LogRuntimeError(ErrorRuntimeCode code, const std::string& desc);
	static void LogRuntimeError(const std::string& desc);

private:
	static std::function<void(const std::string&)> _logger;
	static std::map<ErrorRuntimeCode, std::string> _errorCodeNameMap;
};

} // namespace interpreter
} // namespace peak