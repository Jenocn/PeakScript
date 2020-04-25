#pragma once

#include "Value.h"

namespace peak {
namespace interpreter {
class ValueNumber : public Value {
public:
	void SetValue(double value);
	double GetValue() const;
private:
	double _value{0};
};
} // namespace interpreter
} // namespace peak