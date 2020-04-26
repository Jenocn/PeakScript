#include "SentenceExpressionMath.h"

using namespace peak::interpreter;

SentenceExpressionMath::SentenceExpressionMath(std::shared_ptr<SentenceExpression> left, std::shared_ptr<SentenceExpression> right)
	: _left(left), _right(right) {
}

bool SentenceExpressionMath::Execute(std::shared_ptr<Space> space) {
	if (!_left || !_left->Execute(space)) {
		return false;
	}
	if (!_right || !_right->Execute(space)) {
		return false;
	}

	auto value = Calculate(_left->GetValue(), _right->GetValue());
	if (!value) {
		return false;
	}
	SetValue(value);
	return true;
}