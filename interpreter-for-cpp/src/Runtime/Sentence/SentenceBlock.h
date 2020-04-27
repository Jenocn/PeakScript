#pragma once

#include "SentenceReturn.h"
#include <list>
#include <memory>

namespace peak::interpreter {

	
class SentenceBlock : public SentenceReturn {
public:
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	void Push(std::shared_ptr<Sentence> sentence);

private:
	std::list<std::shared_ptr<Sentence>> _list;
};
} // namespace peak::interpreter