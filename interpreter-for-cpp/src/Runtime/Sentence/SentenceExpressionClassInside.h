/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"

namespace peak::interpreter {
class SentenceExpressionClassInside : public SentenceExpression {
public:
	SentenceExpressionClassInside(const std::list<std::shared_ptr<SentenceExpression>>& insideList);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::ClassInside; }

private:
	std::list<std::shared_ptr<SentenceExpression>> _insideList;
};
} // namespace peak::interpreter