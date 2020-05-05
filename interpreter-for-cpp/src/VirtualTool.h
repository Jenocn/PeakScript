/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace peak {

class VirtualTool {
public:
	static std::string OpenFile(const std::string& filename) {
		std::ifstream in(filename.c_str(), std::ios::in | std::ios::ate);
		if (!in.is_open()) {
			return "";
		}
		std::string result;
		std::size_t size = (std::size_t)in.tellg();
		if (size > 0) {
			in.seekg(std::ios::beg);
			char* buffer = new char[size];
			memset(buffer, 0, size);
			in.read(buffer, size);
			result = buffer;
			delete[] buffer;
		}
		in.close();
		return result;
	}
};
} // namespace peak