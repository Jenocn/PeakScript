#pragma once

#include "SentenceExpression.h"

namespace peak::interpreter {

class IValueCalculate;

class SentenceExpressionAssign : public SentenceExpression {
public:
	SentenceExpressionAssign(const std::string& name, std::shared_ptr<SentenceExpression> expression, std::shared_ptr<IValueCalculate> calculate);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space) final;

private:
	using SentenceExpression::SetValue;

private:
	std::string _name;
	std::shared_ptr<SentenceExpression> _expression{nullptr};
	std::shared_ptr<IValueCalculate> _calculate{nullptr};
};
} // namespace peak::interpreter