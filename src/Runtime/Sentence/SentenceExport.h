/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Sentence.h"

namespace peak {
namespace interpreter {

class SentenceExport : public Sentence {
public:
	SentenceExport(const std::string& moduleName);

	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _moduleName;
};

} // namespace interpreter
} // namespace peak