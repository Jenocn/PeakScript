/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "VirtualJourney.h"
#include <memory>
#include <string>

namespace peak {
class VirtualMachine {
public:
	std::shared_ptr<VirtualJourney> Load(const std::string& src);
};
} // namespace peak