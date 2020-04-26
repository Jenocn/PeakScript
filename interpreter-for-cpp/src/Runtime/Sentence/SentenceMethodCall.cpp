#include "SentenceMethodCall.h"
#include "../Method.h"

using namespace peak::interpreter;

SentenceMethodCall::SentenceMethodCall(const std::string& name)
	: _name(name) {
}

ExecuteResult SentenceMethodCall::Execute(std::shared_ptr<Space> space) {
	auto method = space->FindMethod(_name);
	if (!method) {
		return ExecuteResult::Failed;
	}
	std::vector<std::shared_ptr<Value>> tempArgs;
	for (auto arg : _args) {
		if (!IsSuccess(arg->Execute(space))) {
			return ExecuteResult::Failed;
		}
		tempArgs.emplace_back(arg->GetValue());
	}
	auto resultValue = method->Execute(space, tempArgs);
	if (!resultValue) {
		return ExecuteResult::Failed;
	}
	SetValue(resultValue);
	return ExecuteResult::Successed;
}