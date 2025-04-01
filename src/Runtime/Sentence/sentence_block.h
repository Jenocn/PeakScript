/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "sentence_return.h"

namespace peak { 

	
class SentenceBlock : public SentenceReturn {
public:
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	void Push(std::shared_ptr<Sentence> sentence);

private:
	std::list<std::shared_ptr<Sentence>> _list;
};

} // namespace peak