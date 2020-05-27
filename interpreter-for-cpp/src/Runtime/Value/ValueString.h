/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"

namespace peak { 
namespace interpreter {
class ValueString : public TypeValue<ValueString> {
public:
	ValueString(const std::string& value);
	const std::string& GetValue() const;
	virtual std::string ToString() const;
	virtual std::shared_ptr<Value> Clone() const;

private:
	std::string _value;
};
} // namespace interpreter
} // namespace peak