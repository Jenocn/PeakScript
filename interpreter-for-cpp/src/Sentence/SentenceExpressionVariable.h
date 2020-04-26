#pragma once

#include "SentenceExpression.h"

namespace peak::interpreter {

class Value;

class SentenceExpressionVariable : public SentenceExpression {
public:
	SentenceExpressionVariable(std::string name);
	virtual bool Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
};
} // namespace peak::interpreter