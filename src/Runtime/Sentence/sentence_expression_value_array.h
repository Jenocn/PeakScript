/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"

namespace peak { 
namespace interpreter {

class Value;

class SentenceExpressionValueArray : public SentenceExpression {
public:
	SentenceExpressionValueArray(const std::vector<std::shared_ptr<SentenceExpression>>& valueExpressionArray);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::vector<std::shared_ptr<SentenceExpression>> _expressionArray;
};
} // namespace interpreter
} // namespace peak