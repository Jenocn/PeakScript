/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Base/CommonInclude.h"

namespace peak {

class VirtualTool {
public:
	static std::string OpenFile(const std::string& filename) {
		std::ifstream in(filename);
		std::stringstream buffer;
		buffer << in.rdbuf();
		return buffer.str();
	}
};
} // namespace peak