/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "base/error_logger.h"

namespace peak {

class Module;
class Executer;

class ModulePool {
public:
	static ModulePool* GetInstance();

	bool AddModule(const std::string& moduleName, std::shared_ptr<Module> module);
	void RemoveModule(const std::string& moduleName);

	std::shared_ptr<Module> UseModule(const std::string& moduleName);

private:
	std::pair<std::string, std::string>* _LoadSrc(const std::string& filename);

private:
	std::unordered_map<std::string, std::shared_ptr<Module>> _modulesMap;
};

} // namespace peak