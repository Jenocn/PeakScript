#pragma once

#include "Sentence.h"

namespace peak::interpreter {
class SentenceExpression;
class SentenceLoop : public Sentence {
public:
	SentenceLoop(const std::string& indexParam, std::shared_ptr<SentenceExpression> condition, std::shared_ptr<Sentence> sentence);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<SentenceExpression> _condition{nullptr};
	std::shared_ptr<Sentence> _sentence{nullptr};
	std::string _indexParam;
};
} // namespace peak::interpreter