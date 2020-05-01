/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak::interpreter {

class SentenceExpression;

class SentenceVariableSet : public Sentence {
public:
	SentenceVariableSet(const std::string& name, std::shared_ptr<SentenceExpression> expression);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	std::shared_ptr<SentenceExpression> _expression{nullptr};
};
} // namespace peak::interpreter