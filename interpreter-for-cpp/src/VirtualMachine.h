/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "VirtualJourney.h"

namespace peak {

namespace interpreter {
class ModulePool;
} // namespace interpreter

class VirtualMachine {
public:
	static std::shared_ptr<VirtualJourney> Load(const std::string& src);
	static std::shared_ptr<VirtualJourney> LoadFile(const std::string& filename);

	static void LocateLogger(std::function<void(const std::string&)> logger);
	static void LocateLogger(std::function<void(const std::string&)> echo, std::function<void(const std::string&)> errorLogger);
	static void LocateOpenSrc(std::function<std::string(const std::string&)> func);

	static interpreter::ModulePool* GetModulePool();
};
} // namespace peak