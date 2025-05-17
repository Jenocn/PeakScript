#include "value_bool.h"

using namespace peak;

const std::shared_ptr<ValueBool> ValueBool::TRUE = std::make_shared<ValueBool>(true);
const std::shared_ptr<ValueBool> ValueBool::FALSE = std::make_shared<ValueBool>(false);

ValueBool::ValueBool(bool value)
	: _value(value) {
}

bool ValueBool::GetValue() const {
	return _value;
}

std::string ValueBool::ToString() const {
	return _value ? "true" : "false";
}

std::shared_ptr<Value> ValueBool::Clone() const {
	return _value ? TRUE : FALSE;
}
