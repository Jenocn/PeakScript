#include "ModulePool.h"
#include "Executer.h"
#include "Module.h"
#include "System.h"

using namespace peak::interpreter;

ModulePool* ModulePool::GetInstance() {
	static ModulePool _ins;
	return &_ins;
}

void ModulePool::AddSearchDir(const std::string& dir) {
	if (_searchDirs.find(dir) == _searchDirs.end()) {
		_searchDirs.emplace(dir);
	}
}
void ModulePool::RemoveSearchDir(const std::string& dir) {
	if (_searchDirs.find(dir) != _searchDirs.end()) {
		_searchDirs.erase(dir);
	}
}

bool ModulePool::AddModule(const std::string& moduleName, std::shared_ptr<Module> module) {
	auto ite = _modulesMap.find(moduleName);
	if (ite == _modulesMap.end()) {
		_modulesMap.emplace(moduleName, module);
		return true;
	}
	return false;
}

void ModulePool::RemoveModule(const std::string& moduleName) {
	auto ite = _modulesMap.find(moduleName);
	if (ite != _modulesMap.end()) {
		_modulesMap.erase(ite);
	}
}

bool ModulePool::AddModuleFilename(const std::string& moduleName, const std::string& filename) {
	if (_moduleToFilesMap.find(moduleName) == _moduleToFilesMap.end()) {
		_moduleToFilesMap.emplace(moduleName, filename);
		return true;
	}
	return false;
}

std::shared_ptr<Module> ModulePool::UseModule(const std::string& moduleName) {
	// exists module
	do {
		auto ite = _modulesMap.find(moduleName);
		if (ite == _modulesMap.end()) {
			break;
		}
		auto mod = ite->second;
		if (!mod) {
			_modulesMap.erase(ite);
			break;
		}
		if (!mod->IsExecuted()) {
			if (!mod->Execute()) {
				_modulesMap.erase(ite);
				break;
			}
		}
		return mod;
	} while (false);

	// create new module
	auto executer = _CreateExecuter(moduleName);
	if (!executer) {
		auto ite = _moduleToFilesMap.find(moduleName);
		if (ite != _moduleToFilesMap.end()) {
			executer = _CreateExecuter(ite->second);
		}

		if (!executer) {
			return nullptr;
		}
	}

	auto ret = std::shared_ptr<Module>(new Module(moduleName, executer));
	if (ret->Execute()) {
		_modulesMap.emplace(moduleName, ret);
	} else {
		ret = nullptr;
	}
	return ret;
}

std::shared_ptr<Executer> ModulePool::_CreateExecuter(const std::string& filename) const {
	const auto& src = System::OpenSrc(filename);
	if (!src.empty()) {
		auto ret = Executer::Create(src);
		if (ret) {
			return ret;
		}
	}
	for (auto& dir : _searchDirs) {
		const auto& src = System::OpenSrc(dir + filename);
		if (!src.empty()) {
			auto ret = Executer::Create(src);
			if (ret) {
				return ret;
			}
		}
	}
	return nullptr;
}
