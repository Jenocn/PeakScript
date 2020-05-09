/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak::interpreter {

class SentenceExpression;

class SentenceClassInsideAssign : public Sentence {
public:
	SentenceClassInsideAssign(const std::list<std::shared_ptr<SentenceExpression>>& insideList, std::shared_ptr<SentenceExpression> expression);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::list<std::shared_ptr<SentenceExpression>> _insideList;
	std::shared_ptr<SentenceExpression> _sentenceExpression{nullptr};
};
} // namespace peak::interpreter