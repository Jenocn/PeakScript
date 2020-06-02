/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Base/CommonInclude.h"

namespace peak {
namespace interpreter {

class Space;
class Variable;

class BuiltIn {
public:
	static BuiltIn* GetInstance();

	std::shared_ptr<Variable> FindVariable(const std::string& name) const;

private:
	void _InitFunction();
	void _InitUsing();

private:
	BuiltIn();

private:
	std::unordered_map<std::string, std::shared_ptr<Variable>> _variables;
};
} // namespace interpreter
} // namespace peak