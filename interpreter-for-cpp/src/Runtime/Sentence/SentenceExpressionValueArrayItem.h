/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"

namespace peak::interpreter {
class SentenceExpressionValueArrayItem : public SentenceExpression {
public:
	SentenceExpressionValueArrayItem(std::shared_ptr<SentenceExpression> expressionValue, const std::vector<std::shared_ptr<SentenceExpression>>& indexExpression);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::ArrayItem; }

private:
	std::shared_ptr<SentenceExpression> _sentenceExpression{nullptr};
	std::vector<std::shared_ptr<SentenceExpression>> _indexExpressionVec;
};
} // namespace peak::interpreter