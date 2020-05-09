/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"
#include <vector>

namespace peak::interpreter {

class SentenceExpressionFunctionCall : public SentenceExpression {
public:
	SentenceExpressionFunctionCall(const std::string& name, const std::vector<std::shared_ptr<SentenceExpression>>& args);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

	virtual ExpressionType GetExpressionType() const { return ExpressionType::Function; }

	const std::string& GetFunctionName() const;

private:
	std::string _name;
	std::vector<std::shared_ptr<SentenceExpression>> _args;
};
} // namespace peak::interpreter