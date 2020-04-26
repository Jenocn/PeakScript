#pragma once

#include "Sentence.h"

namespace peak::interpreter {

class Variable;
class SentenceExpression;

class SentenceVar : public Sentence {
public:
	SentenceVar(const std::string& name, std::shared_ptr<SentenceExpression> expression);
	virtual bool Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<Variable> _variable{nullptr};
	std::shared_ptr<SentenceExpression> _expression{nullptr};
};
} // namespace peak::interpreter