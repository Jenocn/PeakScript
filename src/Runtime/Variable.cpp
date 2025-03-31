#include "Variable.h"
#include "Value/ValueNull.h"

using namespace peak::interpreter;

Variable::Variable(const std::string& name, VariableAttribute attribute, std::shared_ptr<Value> value)
	: _name(name), _attribute(attribute) {
	if (value) {
		_value = value;
	} else {
		_value = ValueNull::DEFAULT_VALUE;
	}
}

VariableAttribute Variable::GetAttribute() const {
	return _attribute;
}

const std::string& Variable::GetName() const {
	return _name;
}

bool Variable::SetValue(std::shared_ptr<Value> value) {
	switch (_attribute) {
	case VariableAttribute::None:
		_value = value;
		return true;
	case VariableAttribute::Const:
		ErrorLogger::LogRuntimeError(_name);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Variable, "Can't set value, The variable \"" + _name + "\" is 'const'!");
		return false;
	}
	return true;
}
std::shared_ptr<Value> Variable::GetValue() const {
	return _value;
}