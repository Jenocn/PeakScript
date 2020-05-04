/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <memory>
#include <string>

namespace peak::interpreter {

class Value;

enum class VariableAttribute {
	None,
	Const,
};

class Variable {
public:
	Variable(const std::string& name, VariableAttribute attribute, std::shared_ptr<Value> value = nullptr);

	const std::string& GetName() const;

	bool SetValue(std::shared_ptr<Value> value);
	std::shared_ptr<Value> GetValue() const;

private:
	std::string _name;
	VariableAttribute _attribute{VariableAttribute::None};
	std::shared_ptr<Value> _value{nullptr};
};
} // namespace peak::interpreter