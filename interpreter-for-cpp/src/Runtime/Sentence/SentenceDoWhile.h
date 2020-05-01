/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak::interpreter {
class SentenceExpression;
class SentenceDoWhile : public Sentence {
public:
	SentenceDoWhile(std::shared_ptr<SentenceExpression> expression, std::shared_ptr<Sentence> sentence);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<SentenceExpression> _expression{nullptr};
	std::shared_ptr<Sentence> _sentence{nullptr};
};
} // namespace peak::interpreter