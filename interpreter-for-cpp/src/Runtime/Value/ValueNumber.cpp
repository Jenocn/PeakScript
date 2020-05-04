#include "ValueNumber.h"

using namespace peak::interpreter;

ValueNumber::ValueNumber(double value)
	: _value(value) {
}

double ValueNumber::GetValue() const {
	return _value;
}
std::string ValueNumber::ToString() const {
	char ch[24];
	sprintf(ch, "%0.15lg", _value);
	return ch;
}