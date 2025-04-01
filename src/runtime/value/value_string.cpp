#include "value_string.h"

using namespace peak;

ValueString::ValueString(const std::string& value)
	: _value(value) {
}
const std::string& ValueString::GetValue() const {
	return _value;
}
std::string ValueString::ToString() const {
	return _value;
}
std::shared_ptr<Value> ValueString::Clone() const {
	return std::shared_ptr<Value>(new ValueString(_value));
}
