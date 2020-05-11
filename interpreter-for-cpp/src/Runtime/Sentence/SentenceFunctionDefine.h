/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak::interpreter {

class Variable;

class SentenceFunctionDefine : public Sentence {
public:
	SentenceFunctionDefine(const std::string& name, const std::vector<std::string>& params, std::shared_ptr<Sentence> content);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::vector<std::string> _params;
	std::shared_ptr<Sentence> _content{nullptr};
	std::shared_ptr<Variable> _variable{nullptr};
};
} // namespace peak::interpreter