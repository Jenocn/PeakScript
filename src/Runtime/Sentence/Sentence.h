/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "runtime/space.h"

namespace peak { 

class Value;

enum class ExecuteResult {
	Successed,
	Failed,
	Return,
	Continue,
	Break,
};
class Sentence {
public:
	Sentence() {}
	virtual ~Sentence() {}
	virtual ExecuteResult Execute(std::shared_ptr<Space> space) = 0;

	static bool IsSuccess(ExecuteResult value) {
		return value != ExecuteResult::Failed;
	}
};

} // namespace peak