#include "sentence_expression_double.h"
#include "runtime/value/value_calculate.h"
#include "runtime/value/value_tool.h"
#include "runtime/variable.h"
#include "sentence_expression_variable.h"

using namespace peak;

SentenceExpressionDouble::SentenceExpressionDouble(std::shared_ptr<SentenceExpression> variableExpresison, IValueCalculate* calculate, bool last)
	: _variableExpresison(variableExpresison), _calculate(calculate), _bLast(last) {
}

ExecuteResult SentenceExpressionDouble::Execute(std::shared_ptr<Space> space) {
	if (_variableExpresison->GetExpressionType() != ExpressionType::Variable) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ExpressionDouble, "The expression isn't a type of variable!");
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_variableExpresison->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ExpressionDouble, "The expression execute failed!");
		return ExecuteResult::Failed;
	}
	auto variable = std::static_pointer_cast<SentenceExpressionVariable>(_variableExpresison)->GetVariable();
	auto value = _variableExpresison->GetValue();
	if (!ValueTool::IsNumber(value)) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ExpressionDouble, "The value of variable isn't a type of 'number'!");
		return ExecuteResult::Failed;
	}
	auto ret = _calculate->Calculate(value, std::shared_ptr<Value>(new ValueNumber(1)));
	if (!ret) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ExpressionDouble, "The calculate is failed!");
		return ExecuteResult::Failed;
	}
	if (!variable->SetValue(ret)) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ExpressionDouble, "The variable set value failed!");
		return ExecuteResult::Failed;
	}
	SetValue(_bLast ? value : ret);
	return ExecuteResult::Successed;
}