
#include "SentenceBlock.h"
#include "../Space.h"

using namespace peak::interpreter;

bool SentenceBlock::Execute(std::shared_ptr<Space> space) {
	auto tempSpace = std::shared_ptr<Space>(new Space(space));
	for (auto sentence : _list) {
		if (!sentence->Execute(tempSpace)) {
			return false;
		}
	}
	return true;
}
void SentenceBlock::Push(std::shared_ptr<Sentence> sentence) {
	_list.emplace_back(sentence);
}