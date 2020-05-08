#include "ValueClassInstance.h"
#include "../ClassTemplate.h"
#include "../Variable.h"
#include "ValueTool.h"

using namespace peak::interpreter;

ValueClassInstance::ValueClassInstance(std::shared_ptr<ClassTemplate> classTemplate)
	: _classTemplate(classTemplate->Clone()) {
}
std::shared_ptr<Variable> ValueClassInstance::FindVariable(const std::string& name) const {
	return _classTemplate->FindPublicVariable(name);
}
bool ValueClassInstance::ExecuteConstruct(const std::vector<std::shared_ptr<Value>>& args) {
	auto variable = _classTemplate->FindPublicVariable(_classTemplate->GetName());
	if (!variable) {
		return false;
	}
	auto value = variable->GetValue();
	if (!ValueTool::IsFunction(value)) {
		return false;
	}
	auto func = std::static_pointer_cast<ValueFunction>(value);
	auto result = func->Call(args, _classTemplate->GetSpaceOfThis());
	if (!result) {
		return false;
	}
	return true;
}