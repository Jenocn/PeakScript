#include "SentenceExpressionAssign.h"
#include "../Value/IValueCalculate.h"
#include "../Variable.h"

using namespace peak::interpreter;
SentenceExpressionAssign::SentenceExpressionAssign(const std::string& name, std::shared_ptr<SentenceExpression> expression, std::shared_ptr<IValueCalculate> calculate)
	: _name(name), _expression(expression), _calculate(calculate) {
}
ExecuteResult SentenceExpressionAssign::Execute(std::shared_ptr<Space> space) {
	if (!_expression || !_calculate) {
		return ExecuteResult::Failed;
	}
	auto findVariable = space->FindVariable(_name);
	if (!findVariable) {
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_expression->Execute(space))) {
		return ExecuteResult::Failed;
	}
	auto newValue = _calculate->Calculate(findVariable->GetValue(), _expression->GetValue());
	if (!newValue) {
		return ExecuteResult::Failed;
	}
	findVariable->SetValue(newValue);
	SetValue(newValue);

	return ExecuteResult::Successed;
}