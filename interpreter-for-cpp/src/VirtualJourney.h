/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Runtime/Sentence/Sentence.h"
#include "Runtime/Space.h"

namespace peak {

using peak::interpreter::Sentence;
using peak::interpreter::Space;

class VirtualJourney {
public:
	VirtualJourney();
	VirtualJourney(std::shared_ptr<Space> parent);

	bool Execute();

private:
	std::shared_ptr<Space> _space{nullptr};
	std::shared_ptr<Sentence> _sentence{nullptr};
};
} // namespace peak