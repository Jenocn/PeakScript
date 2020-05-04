
#include "SentenceVariableAssign.h"
#include "../Variable.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceVariableAssign::SentenceVariableAssign(const std::string& name, std::shared_ptr<SentenceExpression> expression)
	: _name(name), _expression(expression) {
}

ExecuteResult SentenceVariableAssign::Execute(std::shared_ptr<Space> space) {
	if (!_expression || !IsSuccess(_expression->Execute(space))) {
		return ExecuteResult::Failed;
	}
	auto findVariable = space->FindVariable(_name);
	if (!findVariable) {
		return ExecuteResult::Failed;
	}
	if (!findVariable->SetValue(_expression->GetValue())) {
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}