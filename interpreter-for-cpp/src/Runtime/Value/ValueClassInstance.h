/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"

namespace peak::interpreter {

class ClassTemplate;
class Variable;

class ValueClassInstance : TypeValue<ValueClassInstance> {
public:
	ValueClassInstance(std::shared_ptr<ClassTemplate> classTemplate);
	std::shared_ptr<Variable> FindVariable(const std::string& name) const;

private:
	std::shared_ptr<ClassTemplate> _classTemplate{nullptr};
};
} // namespace peak::interpreter