/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"

namespace peak::interpreter {

class IValueCalculate;

class SentenceExpressionMath : public SentenceExpression {
public:
	SentenceExpressionMath(std::shared_ptr<SentenceExpression> left, std::shared_ptr<SentenceExpression> right, std::shared_ptr<IValueCalculate> calculate);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::Math; }

protected:
	std::shared_ptr<SentenceExpression> _left{nullptr};
	std::shared_ptr<SentenceExpression> _right{nullptr};
	std::shared_ptr<IValueCalculate> _calculate{nullptr};
};
} // namespace peak::interpreter