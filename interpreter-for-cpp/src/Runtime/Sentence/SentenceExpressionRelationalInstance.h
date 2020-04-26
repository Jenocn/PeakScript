#pragma once

#include "SentenceExpressionMath.h"

namespace peak::interpreter {
class SentenceExpressionRelationalSame : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionRelationalNotSame : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionRelationalMore : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionRelationalSameOrMore : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionRelationalLess : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
class SentenceExpressionRelationalSameOrLess : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual std::shared_ptr<Value> Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
};
} // namespace peak::interpreter