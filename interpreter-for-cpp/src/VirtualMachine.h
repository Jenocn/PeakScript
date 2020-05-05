/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "VirtualJourney.h"

namespace peak {

class VirtualMachine {
public:
	static std::shared_ptr<VirtualJourney> Load(const std::string& src, std::shared_ptr<interpreter::Space> parent = nullptr);
	static std::shared_ptr<VirtualJourney> LoadFile(const std::string& filename, std::shared_ptr<interpreter::Space> parent = nullptr);
};
} // namespace peak