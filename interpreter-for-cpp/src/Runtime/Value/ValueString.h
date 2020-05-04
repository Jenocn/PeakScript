/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"
#include <string>

namespace peak::interpreter {
class ValueString : public TypeValue<ValueString> {
public:
	ValueString(const std::string& value);
	const std::string& GetValue() const;
	virtual std::string ToString() const;

private:
	std::string _value;
};
} // namespace peak::interpreter