/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "sentence_expression.h"

namespace peak {


class SentenceExpressionNot : public SentenceExpression {
public:
	SentenceExpressionNot(std::shared_ptr<SentenceExpression> expression);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::Not; }
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<SentenceExpression> _expression{nullptr};
};


} // namespace peak