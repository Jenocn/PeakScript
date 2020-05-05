/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "VirtualJourney.h"

namespace peak {

class VirtualMachine {
public:
	std::shared_ptr<VirtualJourney> Load(const std::string& src, std::shared_ptr<interpreter::Space> parent = nullptr);
};
} // namespace peak