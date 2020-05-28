/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"

namespace peak {
namespace interpreter {

class SentenceExpressionInside : public SentenceExpression {
public:
	SentenceExpressionInside(std::shared_ptr<SentenceExpression> header, std::vector<std::shared_ptr<SentenceExpression>> insides);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::Inside; }

private:
	std::shared_ptr<SentenceExpression> _header{nullptr};
	std::vector<std::shared_ptr<SentenceExpression>> _insides{nullptr};
};

} // namespace interpreter
} // namespace peak