#pragma once

#include "../Space.h"

namespace peak::interpreter {

class Value;

enum class ExecuteResult {
	Successed,
	Failed,
	Return,
};
class Sentence {
public:
	Sentence() {}
	virtual ~Sentence() {}
	virtual ExecuteResult Execute(std::shared_ptr<Space> space) = 0;

	static bool IsSuccess(ExecuteResult value) {
		return value != ExecuteResult::Failed;
	}

private:
	Sentence(const Sentence&);
	Sentence& operator=(const Sentence&);
};
} // namespace peak::interpreter