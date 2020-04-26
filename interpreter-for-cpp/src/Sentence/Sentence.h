#pragma once

#include "../Space.h"

namespace peak::interpreter {
enum class ExecuteResult {
	Successed,
	Failed,
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