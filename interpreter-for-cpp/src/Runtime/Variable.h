/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <memory>
#include <string>

namespace peak::interpreter {

class Value;

class Variable {
public:
	Variable(const std::string& name);

	const std::string& GetName() const;

	void SetValue(std::shared_ptr<Value> value);
	std::shared_ptr<Value> GetValue() const;

private:
	std::string _name;
	std::shared_ptr<Value> _value{nullptr};
};
} // namespace peak::interpreter