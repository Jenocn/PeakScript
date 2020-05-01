/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"

namespace peak::interpreter {

class Value;

class SentenceExpressionVariable : public SentenceExpression {
public:
	SentenceExpressionVariable(const std::string& name);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::Variable; }

	const std::string& GetVariableName() const;

private:
	std::string _name;
};
} // namespace peak::interpreter