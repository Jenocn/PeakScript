#include "ValueNumber.h"

using namespace peak::interpreter;

ValueNumber::ValueNumber(double value)
	: _value(value) {
}

double ValueNumber::GetValue() const {
	return _value;
}