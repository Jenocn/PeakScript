#pragma once

#include "Sentence.h"
#include <list>
#include <memory>

namespace peak::interpreter {
class SentenceBlock : public Sentence {
public:
	virtual bool Execute(std::shared_ptr<Space> space);
	void Push(std::shared_ptr<Sentence> sentence);

private:
	std::list<std::shared_ptr<Sentence>> _list;
	std::shared_ptr<Space> _space{nullptr};
};
} // namespace peak::interpreter