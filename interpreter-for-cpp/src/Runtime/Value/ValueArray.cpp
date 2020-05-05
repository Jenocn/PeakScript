#include "ValueArray.h"

using namespace peak::interpreter;

ValueArray::ValueArray() {
}
ValueArray::ValueArray(const std::vector<std::shared_ptr<Value>>& value)
	: _value(value) {
}
std::string ValueArray::ToString() const {
	std::string ret = "[";
	auto arrSize = _value.size();
	for (auto i = 0u; i < arrSize; ++i) {
		ret += _value[i]->ToString();
		if (i != arrSize - 1) {
			ret += ", ";
		}
	}
	ret += "]";
	return ret;
}

std::vector<std::shared_ptr<Value>>& ValueArray::GetArray() {
	return _value;
}
