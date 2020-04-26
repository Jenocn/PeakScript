#pragma once

#include "SentenceExpression.h"
#include <vector>

namespace peak::interpreter {

class SentenceMethodCall : public SentenceExpression {
public:
	SentenceMethodCall(const std::string& name);

	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	std::vector<std::shared_ptr<SentenceExpression>> _args;
};
} // namespace peak::interpreter