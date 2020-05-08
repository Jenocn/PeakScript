/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"
#include <vector>

namespace peak::interpreter {
class SentenceExpressionClassNew : public SentenceExpression {
public:
	SentenceExpressionClassNew(const std::string& className, const std::vector<std::shared_ptr<SentenceExpression>>& args);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::ClassNew; }

private:
	std::string _className;
	std::vector<std::shared_ptr<SentenceExpression>> _args;
};
} // namespace peak::interpreter