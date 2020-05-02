#include "SentenceFunctionCall.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceFunctionCall::SentenceFunctionCall(const std::string& name)
	: _name(name) {
}

ExecuteResult SentenceFunctionCall::Execute(std::shared_ptr<Space> space) {
	auto findVariable = space->FindVariable(_name);
	if (!findVariable) {
		return ExecuteResult::Failed;
	}
	auto value = findVariable->GetValue();
	if (!ValueTool::IsFunction(value)) {
		return ExecuteResult::Failed;
	}
	auto func = std::static_pointer_cast<ValueFunction>(value);
	
	std::vector<std::shared_ptr<Value>> tempArgs;
	for (auto arg : _args) {
		if (!IsSuccess(arg->Execute(space))) {
			return ExecuteResult::Failed;
		}
		tempArgs.emplace_back(arg->GetValue());
	}
	auto resultValue = func->Execute(space, tempArgs);
	if (!resultValue) {
		return ExecuteResult::Failed;
	}
	SetValue(resultValue);
	return ExecuteResult::Successed;
}