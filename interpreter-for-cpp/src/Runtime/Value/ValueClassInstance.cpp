#include "ValueClassInstance.h"
#include "../ClassTemplate.h"
#include "../Space.h"
#include "../Variable.h"
#include "ValueTool.h"

using namespace peak::interpreter;

ValueClassInstance::ValueClassInstance(std::shared_ptr<ClassTemplate> classTemplate)
	: _classTemplate(classTemplate->CreateInstance()) {
}
std::shared_ptr<Variable> ValueClassInstance::FindVariable(const std::string& name) const {
	return _classTemplate->FindPublicVariable(name);
}
bool ValueClassInstance::ExecuteConstruct(const std::vector<std::shared_ptr<Value>>& args) {
	return _ExecuteConstruct(_classTemplate, args);
}

bool ValueClassInstance::_ExecuteConstruct(std::shared_ptr<ClassTemplate> classTemplate, const std::vector<std::shared_ptr<Value>>& args) {

	if (!classTemplate) {
		return true;
	}

	if (!_ExecuteConstruct(classTemplate->GetParent(), args)) {
		return false;
	}

	auto variable = classTemplate->FindPublicVariable(classTemplate->GetName());
	if (variable) {
		auto value = variable->GetValue();
		if (!ValueTool::IsFunction(value)) {
			return false;
		}
		auto func = std::static_pointer_cast<ValueFunction>(value);
		auto result = func->Call(args, classTemplate->GetSpaceOfThis());
		if (!result) {
			return false;
		}
	}
	return true;
}

std::string ValueClassInstance::ToString() const {
	return "class { instance of " + _classTemplate->GetName() + " }";
}

std::shared_ptr<Space> ValueClassInstance::GetPublicSpace() const {
	return _classTemplate->GetPublicSpace();
}
std::shared_ptr<Space> ValueClassInstance::GetSpaceOfThis() const {
	return _classTemplate->GetSpaceOfThis();
}
