#include "SentenceExpressionMath.h"

using namespace peak::interpreter;

SentenceExpressionMath::SentenceExpressionMath(std::shared_ptr<SentenceExpression> left, std::shared_ptr<SentenceExpression> right)
	: _left(left), _right(right) {
}

ExecuteResult SentenceExpressionMath::Execute(std::shared_ptr<Space> space) {
	if (!_left || !IsSuccess(_left->Execute(space))) {
		return ExecuteResult::Failed;
	}
	if (!_right || !IsSuccess(_right->Execute(space))) {
		return ExecuteResult::Failed;
	}

	auto value = Calculate(_left->GetValue(), _right->GetValue());
	if (!value) {
		return ExecuteResult::Failed;
	}
	SetValue(value);
	return ExecuteResult::Successed;
}