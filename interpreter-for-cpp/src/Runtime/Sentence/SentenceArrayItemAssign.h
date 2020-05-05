/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"
#include <vector>

namespace peak::interpreter {

class SentenceExpression;

class SentenceArrayItemAssign : public Sentence {
public:
	SentenceArrayItemAssign(const std::string& name, const std::vector<std::shared_ptr<SentenceExpression>>& indexExpressionVec, std::shared_ptr<SentenceExpression> expression);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	std::vector<std::shared_ptr<SentenceExpression>> _indexExpressionVec;
	std::shared_ptr<SentenceExpression> _expression{nullptr};
};
} // namespace peak::interpreter