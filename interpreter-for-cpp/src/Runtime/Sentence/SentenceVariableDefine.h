/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak::interpreter {

class Variable;
class SentenceExpression;

class SentenceVariableDefine : public Sentence {
public:
	SentenceVariableDefine(const std::string& name, std::shared_ptr<SentenceExpression> expression = nullptr);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<Variable> _variable{nullptr};
	std::shared_ptr<SentenceExpression> _expression{nullptr};
};
} // namespace peak::interpreter