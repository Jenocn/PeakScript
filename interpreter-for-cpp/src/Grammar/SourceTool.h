#pragma once

#include "../Runtime/Sentence/Sentence.h"

namespace peak::interpreter {
class SourceTool {
	static std::shared_ptr<Sentence> Parse(const std::string& src);
};
} // namespace peak::interpreter