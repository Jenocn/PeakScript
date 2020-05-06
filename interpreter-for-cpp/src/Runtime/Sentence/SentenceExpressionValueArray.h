/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpressionValue.h"
#include <vector>

namespace peak::interpreter {

class Value;

class SentenceExpressionValueArray : public SentenceExpressionValue {
public:
	SentenceExpressionValueArray(const std::vector<std::shared_ptr<SentenceExpression>>& valueExpressionArray);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::vector<std::shared_ptr<SentenceExpression>> _expressionArray;
};
} // namespace peak::interpreter