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
		std::ifstream in(filename, std::ios::in | std::ios::ate);
		if (!in.is_open()) {
			return "";
		}
		std::string result;
		std::size_t size = (std::size_t)in.tellg();
		if (size > 0) {
			in.seekg(std::ios::beg);
			result.resize(size);
			in.read(const_cast<char*>(result.data()), size);
		}
		in.close();
		return result;
	}
};
} // namespace peak