/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "sentence_expression.h"

namespace peak { 


class SentenceExpressionVariable;
class IValueCalculate;

class SentenceExpressionDouble : public SentenceExpression {
public:
	SentenceExpressionDouble(std::shared_ptr<SentenceExpression> variableExpresison, IValueCalculate* calculate, bool last);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

	virtual ExpressionType GetExpressionType() const { return ExpressionType::DoubleSymbol; }

private:
	std::shared_ptr<SentenceExpression> _variableExpresison{nullptr};
	IValueCalculate* _calculate{nullptr};
	bool _bLast{false};
};

} // namespace peak