#include "VirtualJourney.h"
#include "Runtime/Executer.h"
#include "Runtime/Value/ValueTool.h"
#include "Runtime/Variable.h"
#include "Runtime/Space.h"

using namespace peak;
using namespace peak::interpreter;

VirtualJourney::VirtualJourney(std::shared_ptr<Executer> executer)
	: _executer(executer) {
}

bool VirtualJourney::Execute() {
	return _executer->Execute();
}

std::shared_ptr<Space> VirtualJourney::GetSpace() const {
	return _executer->GetSpace();
}

std::shared_ptr<Variable> VirtualJourney::FindVariable(const std::string& name) const {
	return _executer->FindVariable(name);
}
bool VirtualJourney::AddVariable(std::shared_ptr<Variable> variable) {
	return _executer->AddVariable(variable);
}
std::shared_ptr<Value> VirtualJourney::ExecuteFunction(const std::string& name, const std::vector<std::shared_ptr<Value>>& args) {
	auto variable = _executer->FindVariable(name);
	if (variable && ValueTool::IsFunction(variable->GetValue())) {
		auto valueFunc = std::static_pointer_cast<ValueFunction>(variable->GetValue());
		return valueFunc->Call(args, GetSpace());
	}
	return ValueNull::DEFAULT_VALUE;
}

std::shared_ptr<Value> VirtualJourney::ExecuteFunction(const std::string& name) {
	return ExecuteFunction(name, {});
}
