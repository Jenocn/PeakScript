#pragma once

#include "SentenceExpression.h"

namespace peak::interpreter {
class SentenceExpressionMath : public SentenceExpression {
public:
	SentenceExpressionMath(std::shared_ptr<SentenceExpression> left, std::shared_ptr<SentenceExpression> right);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space) final;

protected:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) = 0;

private:
	using SentenceExpression::SetValue;

private:
	std::shared_ptr<SentenceExpression> _left{nullptr};
	std::shared_ptr<SentenceExpression> _right{nullptr};
};
} // namespace peak::interpreter