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
private:
	struct BuiltIn {
		std::unordered_map<std::string, std::shared_ptr<Variable>> variables;
		BuiltIn();
	};

public:
	static void LocateEcho(std::function<void(const std::string&)> func);

public:
	static void Echo(const std::string& message);
	static std::shared_ptr<Variable> FindVariable(const std::string& name);

private:
	static std::function<void(const std::string&)> _funcEcho;
	static BuiltIn _buildIn;
};
} // namespace interpreter
} // namespace peak