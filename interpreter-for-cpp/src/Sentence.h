#pragma once

#include "Space.h"

namespace peak {
namespace interpreter {

class Sentence {
public:
	virtual ~Sentence() {}
	virtual bool Execute(std::shared_ptr<Space> space) = 0;
};
} // namespace interpreter
} // namespace peak