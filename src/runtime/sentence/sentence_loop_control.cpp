#include "sentence_loop_control.h"

using namespace peak;

ExecuteResult SentenceLoopControlContinue::Execute(std::shared_ptr<Space>) {
	return ExecuteResult::Continue;
}
ExecuteResult SentenceLoopControlBreak::Execute(std::shared_ptr<Space>) {
	return ExecuteResult::Break;
}