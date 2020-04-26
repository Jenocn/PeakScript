#pragma once

#include "Value.h"

namespace peak::interpreter {
class ValueNumber : public TypeValue<ValueNumber> {
public:
	ValueNumber(double value);
	double GetValue() const;

private:
	double _value{0};
};
} // namespace peak::interpreter