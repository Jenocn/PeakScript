
#include "SentenceVariableAssign.h"
#include "../Variable.h"
#include "SentenceExpression.h"
#include "SentenceExpressionVariable.h"

using namespace peak::interpreter;

SentenceVariableAssign::SentenceVariableAssign(std::shared_ptr<SentenceExpression> variableExpression, std::shared_ptr<SentenceExpression> expression)
	: _variableExpression(variableExpression), _expression(expression) {
}

ExecuteResult SentenceVariableAssign::Execute(std::shared_ptr<Space> space) {
	if (!_variableExpression || !_expression) {
		return ExecuteResult::Failed;
	}
	if (_variableExpression->GetExpressionType() != ExpressionType::Variable) {
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_variableExpression->Execute(space))) {
		return ExecuteResult::Failed;
	}
	auto variable = std::static_pointer_cast<SentenceExpressionVariable>(_variableExpression)->GetVariable();
	if (!variable) {
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_expression->Execute(space))) {
		return ExecuteResult::Failed;
	}
	if (!variable->SetValue(_expression->GetValue())) {
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}