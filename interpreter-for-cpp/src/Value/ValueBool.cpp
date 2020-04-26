#include "ValueBool.h"

using namespace peak::interpreter;

ValueBool::ValueBool(bool value)
	: _value(value) {
}

bool ValueBool::GetValue() const {
	return _value;
}