/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "base/error_logger.h"

namespace peak {

class Module;

class BuiltinModule {
public:
	static BuiltinModule* GetInstance();

	std::shared_ptr<Module> FindModule(const std::string& name) const;

private:
	BuiltinModule();

private:
	std::unordered_map<std::string, std::shared_ptr<Module>> _modules;
};
} // namespace peak