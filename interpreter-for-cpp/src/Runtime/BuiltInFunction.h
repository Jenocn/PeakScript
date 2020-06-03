/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Base/CommonInclude.h"

namespace peak {
namespace interpreter {

class Variable;

class BuiltInFunction {
public:
	static BuiltInFunction* GetInstance();

	std::shared_ptr<Variable> FindVariable(const std::string& name) const;

private:
	BuiltInFunction();

private:
	std::unordered_map<std::string, std::shared_ptr<Variable>> _variables;
};
} // namespace interpreter
} // namespace peak