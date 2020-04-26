#pragma once

#include "SentenceExpressionMath.h"

namespace peak::interpreter {
class SentenceExpressionLogicAnd : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionLogicOr : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
} // namespace peak::interpreter