/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Base/CommonInclude.h"

namespace peak {
namespace interpreter {

class Module;
class Executer;

class ModulePool {
public:
	static ModulePool* GetInstance();

	void AddSearchDir(const std::string& dir);
	void RemoveSearchDir(const std::string& dir);

	bool AddModule(const std::string& moduleName, std::shared_ptr<Module> module, bool bExecuted);
	void RemoveModule(const std::string& moduleName);
	bool AddModuleFilename(const std::string& moduleName, const std::string& filename);
	const std::string& GetFilenameOfModule(const std::string& moduleName) const;

	std::shared_ptr<Module> UseModule(const std::string& moduleName);

	bool IsExecuted(const std::string& moduleName) const;

private:
	std::shared_ptr<Executer> _CreateExecuter(const std::string& filename) const;

private:
	std::unordered_map<std::string, std::string> _moduleToFilesMap;
	std::unordered_map<std::string, std::shared_ptr<Module>> _modulesMap;
	std::set<std::string> _executedSet;
	std::set<std::string> _searchDirs;
};

} // namespace interpreter
} // namespace peak