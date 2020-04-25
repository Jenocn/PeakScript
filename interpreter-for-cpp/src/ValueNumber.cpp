#include "ValueNumber.h"

using namespace peak::interpreter;

void ValueNumber::SetValue(double value) {
	_value = value;
}
double ValueNumber::GetValue() const {
	return _value;
}