/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Runtime/Space.h"
#include "Runtime/Value/ValueTool.h"
#include "Runtime/Variable.h"

namespace peak {

namespace interpreter {
class Sentence;
} // namespace interpreter

class VirtualJourney {
public:
	VirtualJourney(const std::list<std::shared_ptr<interpreter::Sentence>>& sentenceList, std::shared_ptr<interpreter::Space> parent = nullptr);

	bool Execute();

public:
	std::shared_ptr<interpreter::Variable> FindVariable(const std::string& name);
	bool AddVariable(std::shared_ptr<interpreter::Variable> variable);

private:
	std::shared_ptr<interpreter::Space> _space{nullptr};
	std::list<std::shared_ptr<interpreter::Sentence>> _sentenceList{nullptr};
};
} // namespace peak