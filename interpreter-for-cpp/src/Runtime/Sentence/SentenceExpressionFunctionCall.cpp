#include "SentenceExpressionFunctionCall.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceExpressionFunctionCall::SentenceExpressionFunctionCall(const std::string& name, const std::vector<std::shared_ptr<SentenceExpression>>& args)
	: _name(name), _args(args) {
}

ExecuteResult SentenceExpressionFunctionCall::Execute(std::shared_ptr<Space> space) {
	auto variable = space->FindVariable(_name);
	if (!variable) {
		return ExecuteResult::Failed;
	}
	auto value = variable->GetValue();
	if (!ValueTool::IsFunction(value)) {
		return ExecuteResult::Failed;
	}
	std::vector<std::shared_ptr<Value>> args;
	for (auto expression : _args) {
		if (!expression || !IsSuccess(expression->Execute(space))) {
			return ExecuteResult::Failed;
		}
		auto arg = expression->GetValue();
		args.emplace_back(arg);
	}
	auto result = std::static_pointer_cast<ValueFunction>(value)->Call(args, space);
	if (!result) {
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}