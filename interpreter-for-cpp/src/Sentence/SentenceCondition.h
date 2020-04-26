#pragma once

#include "SentenceReturn.h"

namespace peak::interpreter {
class SentenceExpression;
class SentenceCondition : public SentenceReturn {
public:
	SentenceCondition(std::shared_ptr<SentenceExpression> expression);
	void SetSentenceWhenTrue(std::shared_ptr<Sentence> sentence);
	void SetSentenceWhenFalse(std::shared_ptr<Sentence> sentence);

	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<SentenceExpression> _expression{nullptr};
	std::shared_ptr<Sentence> _sentenceTrue{nullptr};
	std::shared_ptr<Sentence> _sentenceFalse{nullptr};
};
} // namespace peak::interpreter