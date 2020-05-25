/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak {
namespace interpreter {

class Variable;

class SentenceFunctionDefine : public Sentence {
public:
	SentenceFunctionDefine(const std::string& name, const std::vector<std::string>& params, std::shared_ptr<Sentence> content);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	std::vector<std::string> _params;
	std::shared_ptr<Sentence> _content{nullptr};
};
} // namespace interpreter
} // namespace peak