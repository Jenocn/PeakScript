#include "sentence_expression_math.h"
#include "runtime/value/value_calculate.h"

using namespace peak;

SentenceExpressionMath::SentenceExpressionMath(std::shared_ptr<SentenceExpression> left,
											   std::shared_ptr<SentenceExpression> right,
											   IValueCalculate* calculate)
	: _left(left), _right(right), _calculate(calculate) {
}

ExecuteResult SentenceExpressionMath::Execute(std::shared_ptr<Space> space) {
	if (!_left || !IsSuccess(_left->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Math, "The math expression execute failed!");
		return ExecuteResult::Failed;
	}
	if (!_right || !IsSuccess(_right->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Math, "The math expression execute failed!");
		return ExecuteResult::Failed;
	}

	auto value = _calculate->Calculate(_left->GetValue(), _right->GetValue());
	if (!value) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Math, "The math expression execute failed!");
		return ExecuteResult::Failed;
	}
	SetValue(value);
	return ExecuteResult::Successed;
}