#pragma once

#include "SentenceExpressionArithmetic.h"

namespace peak::interpreter {
class SentenceExpressionArithmeticAdd : SentenceExpressionArithmetic {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticSub : SentenceExpressionArithmetic {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticMul : SentenceExpressionArithmetic {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticDiv : SentenceExpressionArithmetic {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticMod : SentenceExpressionArithmetic {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticPow : SentenceExpressionArithmetic {
public:
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
} // namespace peak::interpreter