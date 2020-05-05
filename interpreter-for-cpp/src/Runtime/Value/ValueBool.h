/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"

namespace peak::interpreter {
class ValueBool : public TypeValue<ValueBool> {
public:
	ValueBool(bool value);
	bool GetValue() const;
	virtual std::string ToString() const;

private:
	bool _value{false};
};
} // namespace peak::interpreter