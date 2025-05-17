#include "value_number.h"

using namespace peak;

ValueNumber::ValueNumber(double value)
	: _value(value) {
}

double ValueNumber::GetValue() const {
	return _value;
}
std::string ValueNumber::ToString() const {
	char ch[24] { 0 };
	snprintf(ch, sizeof(ch), "%0.15lg", _value);
	// sprintf(ch, "%0.15lg", _value);
	return ch;
}
std::string ValueNumber::ToRawString() const {
	return ToString();
}

std::shared_ptr<Value> ValueNumber::Clone() const {
	return std::make_shared<ValueNumber>(_value);
}
