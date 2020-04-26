#include "SourceTool.h"
#include "../Runtime/Sentence/SentenceBlock.h"

using namespace peak::interpreter;

std::shared_ptr<Sentence> SourceTool::Parse(const std::string& src) {
	auto sentence = std::shared_ptr<SentenceBlock>(new SentenceBlock());

	for (std::size_t i = 0; i < src.size(); ++i) {
		// temp todo...
	}

	return sentence;
}
