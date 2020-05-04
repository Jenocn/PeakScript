
#include "SentenceVariableDefine.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceVariableDefine::SentenceVariableDefine(const std::string& name, VariableAttribute attribute, std::shared_ptr<SentenceExpression> expression)
	: _name(name), _attribute(attribute), _expression(expression) {
}

ExecuteResult SentenceVariableDefine::Execute(std::shared_ptr<Space> space) {
	std::shared_ptr<Value> value{nullptr};
	if (_expression) {
		if (!IsSuccess(_expression->Execute(space))) {
			return ExecuteResult::Failed;
		}
		value = _expression->GetValue();
		if (!value) {
			return ExecuteResult::Failed;
		}
	} else {
		if (_attribute == VariableAttribute::Const) {
			return ExecuteResult::Failed;
		}
	}
	_variable = std::shared_ptr<Variable>(new Variable(_name, _attribute, value));
	if (!space->AddVariable(_variable)) {
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}