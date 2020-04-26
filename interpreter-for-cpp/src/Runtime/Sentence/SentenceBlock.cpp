
#include "SentenceBlock.h"
#include "../Space.h"
#include "SentenceReturn.h"

using namespace peak::interpreter;

ExecuteResult SentenceBlock::Execute(std::shared_ptr<Space> space) {
	auto tempSpace = std::shared_ptr<Space>(new Space(space->GetSpaceType(), space));
	for (auto sentence : _list) {
		auto executeRet = sentence->Execute(tempSpace);
		if (!IsSuccess(executeRet)) {
			return ExecuteResult::Failed;
		}
		if (executeRet == ExecuteResult::Return) {
			SetReturnValue(std::static_pointer_cast<SentenceReturn>(sentence)->GetReturnValue());
			return ExecuteResult::Return;
		}
	}
	return ExecuteResult::Successed;
}
void SentenceBlock::Push(std::shared_ptr<Sentence> sentence) {
	_list.emplace_back(sentence);
}
