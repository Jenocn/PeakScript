
#include "SentenceVar.h"
#include "SentenceExpression.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceVar::SentenceVar(const std::string& name, std::shared_ptr<SentenceExpression> expression)
	: _expression(expression) {
	_variable = std::shared_ptr<Variable>(new Variable(name));
}

ExecuteResult SentenceVar::Execute(std::shared_ptr<Space> space) {
	if (_expression) {
		if (!IsSuccess(_expression->Execute(space))) {
			return ExecuteResult::Failed;
		}
		_variable->SetValue(_expression->GetValue());
	}
	if (!space->AddVariable(_variable)) {
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}