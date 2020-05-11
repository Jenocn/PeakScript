#include "ValueBool.h"

using namespace peak::interpreter;

const std::shared_ptr<ValueBool> ValueBool::TRUE = std::shared_ptr<ValueBool>(new ValueBool(true));
const std::shared_ptr<ValueBool> ValueBool::FALSE = std::shared_ptr<ValueBool>(new ValueBool(false));

ValueBool::ValueBool(bool value)
	: _value(value) {
}

bool ValueBool::GetValue() const {
	return _value;
}

std::string ValueBool::ToString() const {
	return _value ? "true" : "false";
}
