/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"
#include <vector>

namespace peak::interpreter {
class SentenceMethodDefine : public Sentence {
public:
	SentenceMethodDefine(const std::string& name);
	void PushParam(const std::string& name);
	void SetSentence(std::shared_ptr<Sentence> sentence);

	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	std::vector<std::string> _parameters;
	std::shared_ptr<Sentence> _sentence{nullptr};
};
} // namespace peak::interpreter