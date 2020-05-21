#include "ErrorLogger.h"

using namespace peak::interpreter;

std::function<void(const std::string&)> ErrorLogger::_logger = [](const std::string& message) {
	std::cout << message << std::endl;
};

std::map<ErrorCode, std::string> ErrorLogger::_errorCodeMap = {
	{ErrorCode::None, ""},
	{ErrorCode::EndSign, "Missing \";\""},
	{ErrorCode::SignSpace, "Not found sign"},
	{ErrorCode::Name, "The name is special sign!"},
	{ErrorCode::Bracket, "Missing \"(\" or \")\""},
	{ErrorCode::ConstAssign, "The const variable must assign"},
	{ErrorCode::ForeachIn, "Missing \"in\""},
	{ErrorCode::String, "Missing \"\"\", \"`\", \"'\""},
	{ErrorCode::Array, "Missing \"[\" or \"]\""},
};

void ErrorLogger::ResetErrorCodeMap(const std::map<ErrorCode, std::string>& errorCodeMap) {
	_errorCodeMap = errorCodeMap;
}

void ErrorLogger::Locate(std::function<void(const std::string&)> logger) {
	_logger = logger;
}

void ErrorLogger::Log(const std::string& message) {
	_logger("[!]error:" + message);
}

void ErrorLogger::Log(ErrorCode code, const std::string& info) {
	if (code == ErrorCode::None) {
		return;
	}
	std::string error = "[!]error " + std::to_string((int)code);
	auto ite = _errorCodeMap.find(code);
	if (ite != _errorCodeMap.end()) {
		error += (": " + ite->second);
	}
	error += (": " + info);
	_logger(error);
}
