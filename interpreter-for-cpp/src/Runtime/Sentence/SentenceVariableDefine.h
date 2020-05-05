/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Variable.h"
#include "Sentence.h"

namespace peak::interpreter {

class SentenceExpression;

class SentenceVariableDefine : public Sentence {
public:
	SentenceVariableDefine(const std::string& name, VariableAttribute attribute, std::shared_ptr<SentenceExpression> expression = nullptr);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	VariableAttribute _attribute{VariableAttribute::None};
	std::shared_ptr<Variable> _variable{nullptr};
	std::shared_ptr<SentenceExpression> _expression{nullptr};
};
} // namespace peak::interpreter