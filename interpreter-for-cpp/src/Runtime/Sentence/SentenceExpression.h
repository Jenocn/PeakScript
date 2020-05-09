/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak::interpreter {

class Value;

enum class ExpressionType : char {
	None,
	Math,
	SelfAssign,
	Value,
	Variable,
	Function,
	DoubleSymbol,
	ClassNew,
	ClassInside,
	ArrayItem,
};

class SentenceExpression : public Sentence {
public:
	SentenceExpression();
	SentenceExpression(std::shared_ptr<Value> value);
	std::shared_ptr<Value> GetValue() const;
	virtual ExpressionType GetExpressionType() const = 0;

protected:
	void SetValue(std::shared_ptr<Value> value);

private:
	std::shared_ptr<Value> _value{nullptr};
};
} // namespace peak::interpreter