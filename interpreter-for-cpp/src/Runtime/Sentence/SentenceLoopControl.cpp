#include "SentenceLoopControl.h"

using namespace peak::interpreter;

ExecuteResult SentenceLoopControlContinue::Execute(std::shared_ptr<Space> space) {
	return ExecuteResult::Continue;
}
ExecuteResult SentenceLoopControlBreak::Execute(std::shared_ptr<Space> space) {
	return ExecuteResult::Break;
}