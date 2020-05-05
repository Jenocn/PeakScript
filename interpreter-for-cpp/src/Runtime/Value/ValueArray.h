/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"
#include <vector>

namespace peak::interpreter {
class ValueArray : public TypeValue<ValueArray> {
public:
	ValueArray();
	ValueArray(const std::vector<std::shared_ptr<Value>>& value);
	virtual std::string ToString() const;

	std::vector<std::shared_ptr<Value>>& GetArray();

private:
	std::vector<std::shared_ptr<Value>> _value;
};
} // namespace peak::interpreter