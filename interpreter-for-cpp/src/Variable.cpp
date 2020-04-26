#include "Variable.h"
#include "ValueNull.h"

using namespace peak::interpreter;

Variable::Variable(const std::string& name) : _name(name) {
	_value = std::shared_ptr<Value>(new ValueNull());
}

const std::string& Variable::GetName() const {
	return _name;
}

void Variable::SetValue(std::shared_ptr<Value> value) {
	_value = value;
}
std::shared_ptr<Value> Variable::GetValue() const {
	return _value;
}