#include "ValueString.h"

using namespace peak::interpreter;

ValueString::ValueString(const std::string& value)
	: _value(value) {
}
const std::string& ValueString::GetValue() const {
	return _value;
}