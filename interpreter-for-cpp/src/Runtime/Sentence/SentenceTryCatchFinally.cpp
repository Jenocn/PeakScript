#include "SentenceTryCatchFinally.h"

using namespace peak::interpreter;

SentenceTryCatchFinally::SentenceTryCatchFinally(std::shared_ptr<Sentence> senTry,
												 std::shared_ptr<Sentence> senCatch,
												 std::shared_ptr<Sentence> senFinally)
	: _senTry(senTry), _senCatch(senCatch), _senFinally(senFinally) {
}
ExecuteResult SentenceTryCatchFinally::Execute(std::shared_ptr<Space> space) {
	if (!_senTry) {
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_senTry->Execute(std::shared_ptr<Space>(new Space(SpaceType::None, space))))) {
		if (_senCatch) {
			if (!IsSuccess(_senCatch->Execute(std::shared_ptr<Space>(new Space(SpaceType::None, space))))) {
				return ExecuteResult::Failed;
			}
		}
	}
	if (_senFinally) {
		if (!IsSuccess(_senFinally->Execute(std::shared_ptr<Space>(new Space(SpaceType::None, space))))) {
			return ExecuteResult::Failed;
		}
	}
	return ExecuteResult::Successed;
}