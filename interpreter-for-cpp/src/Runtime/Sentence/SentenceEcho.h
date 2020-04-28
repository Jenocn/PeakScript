#pragma once

#include "Sentence.h"

namespace peak::interpreter {
class SentenceExpression;
class SentenceEcho : public Sentence {
public:
	SentenceEcho(std::shared_ptr<SentenceExpression> expression);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
private:
	std::shared_ptr<SentenceExpression> _expression{nullptr};
};
} // namespace peak::interpreter