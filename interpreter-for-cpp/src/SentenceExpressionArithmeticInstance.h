#pragma once

#include "SentenceExpressionArithmetic.h"

namespace peak::interpreter {
class SentenceExpressionArithmeticAdd : public SentenceExpressionArithmetic {
public:
	using SentenceExpressionArithmetic::SentenceExpressionArithmetic;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticSub : public SentenceExpressionArithmetic {
public:
	using SentenceExpressionArithmetic::SentenceExpressionArithmetic;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticMul : public SentenceExpressionArithmetic {
public:
	using SentenceExpressionArithmetic::SentenceExpressionArithmetic;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticDiv : public SentenceExpressionArithmetic {
public:
	using SentenceExpressionArithmetic::SentenceExpressionArithmetic;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticMod : public SentenceExpressionArithmetic {
public:
	using SentenceExpressionArithmetic::SentenceExpressionArithmetic;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
} // namespace peak::interpreter