#pragma once

#include "Sentence.h"

namespace peak {
namespace interpreter {

class Variable;

class SentenceVarFromName : public Sentence {
public:
	SentenceVarFromName(const std::string& name, const std::string& fromName);
	virtual bool Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<Variable> _variable{nullptr};
	std::string _fromName;
};
} // namespace interpreter
} // namespace peak