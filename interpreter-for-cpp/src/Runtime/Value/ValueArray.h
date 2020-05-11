/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"

namespace peak::interpreter {

class Variable;
	
class ValueArray : public TypeValue<ValueArray> {
public:
	ValueArray();
	ValueArray(const std::vector<std::shared_ptr<Variable>>& value);
	virtual std::string ToString() const;

	std::vector<std::shared_ptr<Variable>>& GetArray();

	void Reserve(std::size_t size);
	void EmplaceBack(std::shared_ptr<Variable> variable);
	void EmplaceBack(std::shared_ptr<Value> value);

private:
	std::vector<std::shared_ptr<Variable>> _value;
};
} // namespace peak::interpreter