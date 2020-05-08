/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"

namespace peak::interpreter {

class ClassTemplate;
class Variable;

class ValueClassInstance : public TypeValue<ValueClassInstance> {
public:
	ValueClassInstance(std::shared_ptr<ClassTemplate> classTemplate);
	std::shared_ptr<Variable> FindVariable(const std::string& name) const;
	bool ExecuteConstruct(const std::vector<std::shared_ptr<Value>>& args);
	virtual std::string ToString() const;

private:
	bool _ExecuteConstruct(std::shared_ptr<ClassTemplate> classTemplate, const std::vector<std::shared_ptr<Value>>& args);

private:
	std::shared_ptr<ClassTemplate> _classTemplate{nullptr};
};
} // namespace peak::interpreter