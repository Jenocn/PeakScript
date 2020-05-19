/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceReturn.h"

namespace peak { 
namespace interpreter {
class SentenceExpression;
class SentenceCondition : public SentenceReturn {
public:
	SentenceCondition(std::shared_ptr<SentenceExpression> expression, std::shared_ptr<Sentence> sentenceTrue, std::shared_ptr<Sentence> sentenceFalse);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<SentenceExpression> _expression{nullptr};
	std::shared_ptr<Sentence> _sentenceTrue{nullptr};
	std::shared_ptr<Sentence> _sentenceFalse{nullptr};
};
} // namespace interpreter
} // namespace peak