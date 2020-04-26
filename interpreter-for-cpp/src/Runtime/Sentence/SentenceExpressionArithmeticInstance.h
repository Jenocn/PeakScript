#pragma once

#include "SentenceExpressionMath.h"

namespace peak::interpreter {
class SentenceExpressionArithmeticAdd : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticSub : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticMul : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticDiv : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionArithmeticMod : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
} // namespace peak::interpreter