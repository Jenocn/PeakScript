#include "ValueArray.h"
#include "../Variable.h"

using namespace peak::interpreter;

ValueArray::ValueArray() {
}
ValueArray::ValueArray(const std::vector<std::shared_ptr<Variable>>& value)
	: _value(value) {
}
std::string ValueArray::ToString() const {
	std::string ret = "[";
	auto arrSize = _value.size();
	for (auto i = 0u; i < arrSize; ++i) {
		ret += _value[i]->GetValue()->ToString();
		if (i != arrSize - 1) {
			ret += ", ";
		}
	}
	ret += "]";
	return ret;
}

std::vector<std::shared_ptr<Variable>>& ValueArray::GetArray() {
	return _value;
}

void ValueArray::Reserve(std::size_t size) {
	_value.reserve(size);
}
void ValueArray::EmplaceBack(std::shared_ptr<Variable> variable) {
	_value.emplace_back(variable);
}
void ValueArray::EmplaceBack(std::shared_ptr<Value> value) {
	auto variable = std::shared_ptr<Variable>(new Variable("", VariableAttribute::None, value));
	_value.emplace_back(variable);
}