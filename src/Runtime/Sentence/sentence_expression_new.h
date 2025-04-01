/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "sentence_expression.h"

namespace peak {

class SentenceExpressionNew : public SentenceExpression {
public:
	SentenceExpressionNew(const std::string& name);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::New; }
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
};


} // namespace peak