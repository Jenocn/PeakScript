/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak::interpreter {
class SentenceClassDefine : public Sentence {
public:
	SentenceClassDefine(const std::string& className,
	const std::string& parentName,
	const std::list<std::shared_ptr<Sentence>>& sentenceOfPrivate,
	const std::list<std::shared_ptr<Sentence>>& sentenceOfPublic,
	const std::list<std::shared_ptr<Sentence>>& sentenceOfStatic);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _className;
	std::string _parentName;
	std::list<std::shared_ptr<Sentence>> _sentenceOfPrivate;
	std::list<std::shared_ptr<Sentence>> _sentenceOfPublic;
	std::list<std::shared_ptr<Sentence>> _sentenceOfStatic;
};
} // namespace peak::interpreter