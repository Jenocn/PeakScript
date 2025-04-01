
#include "sentence_variable_assign.h"
#include "runtime/variable.h"
#include "sentence_expression.h"
#include "sentence_expression_variable.h"

using namespace peak;

SentenceVariableAssign::SentenceVariableAssign(std::shared_ptr<SentenceExpression> variableExpression, std::shared_ptr<SentenceExpression> expression)
	: _variableExpression(variableExpression), _expression(expression) {
}

ExecuteResult SentenceVariableAssign::Execute(std::shared_ptr<Space> space) {
	if (_variableExpression->GetExpressionType() != ExpressionType::Variable) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableAssign, "The result of expression isn't a variable!");
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_variableExpression->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableAssign, "The expression execute failed!");
		return ExecuteResult::Failed;
	}
	auto variable = std::static_pointer_cast<SentenceExpressionVariable>(_variableExpression)->GetVariable();
	if (!IsSuccess(_expression->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableAssign, "The expression execute failed!");
		return ExecuteResult::Failed;
	}
	if (!variable->SetValue(_expression->GetValue())) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableAssign, "The expression execute failed!");
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}