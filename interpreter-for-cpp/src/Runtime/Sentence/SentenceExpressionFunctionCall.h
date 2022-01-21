/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"

namespace peak { 
namespace interpreter {

class SentenceExpressionFunctionCall : public SentenceExpression {
public:
	SentenceExpressionFunctionCall(const std::string& name, const std::vector<std::shared_ptr<SentenceExpression>>& args);

	ExecuteResult ExecuteFromInside(std::shared_ptr<Space> objSpace, std::shared_ptr<Space> space);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

	virtual ExpressionType GetExpressionType() const { return ExpressionType::Function; }

	const std::string& GetFunctionName() const;

private:
	std::string _name;
	std::vector<std::shared_ptr<SentenceExpression>> _args;
};
} // namespace interpreter
} // namespace peak