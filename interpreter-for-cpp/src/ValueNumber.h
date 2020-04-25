#pragma once

#include "Value.h"

namespace peak::interpreter {
class ValueNumber : public Value {
public:
	void SetValue(double value);
	double GetValue() const;

private:
	double _value{0};
};
} // namespace peak::interpreter