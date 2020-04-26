#pragma once

#include "../Space.h"

namespace peak::interpreter {

class Sentence {
public:
	Sentence() {}
	virtual ~Sentence() {}
	virtual bool Execute(std::shared_ptr<Space> space) = 0;

private:
	Sentence(const Sentence&);
	Sentence& operator=(const Sentence&);
};
} // namespace peak::interpreter