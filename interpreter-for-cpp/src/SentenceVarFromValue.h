#pragma once

#include "Sentence.h"

namespace peak {
namespace interpreter {

class Variable;
class Value;

class SentenceVarFromValue : public Sentence {
public:
	SentenceVarFromValue(const std::string& name, std::shared_ptr<Value> fromValue);
	virtual bool Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<Variable> _variable{nullptr};
};
} // namespace interpreter
} // namespace peak