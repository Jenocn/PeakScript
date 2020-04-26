#pragma once

#include "SentenceExpression.h"

namespace peak::interpreter {

class Value;

class SentenceExpressionValue : public SentenceExpression {
public:
	SentenceExpressionValue(std::shared_ptr<Value> value);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<Value> _value{nullptr};
};
} // namespace peak::interpreter