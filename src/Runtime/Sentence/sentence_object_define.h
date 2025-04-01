/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak {
namespace interpreter {

class SentenceObjectDefine : public Sentence {
public:
	SentenceObjectDefine(const std::string& name, const std::string& parentName, std::list<std::shared_ptr<Sentence>>& sentenceList);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	std::string _parentName;
	std::list<std::shared_ptr<Sentence>> _sentenceList;
};

} // namespace interpreter
} // namespace peak