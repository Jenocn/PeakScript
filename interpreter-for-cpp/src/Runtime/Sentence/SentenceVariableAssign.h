#pragma once

#include "Sentence.h"

namespace peak::interpreter {

class Variable;
class SentenceExpression;

class SentenceVariableAssign : public Sentence {
public:
	SentenceVariableAssign(const std::string& name, std::shared_ptr<SentenceExpression> expression);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	std::shared_ptr<SentenceExpression> _expression{nullptr};
};
} // namespace peak::interpreter