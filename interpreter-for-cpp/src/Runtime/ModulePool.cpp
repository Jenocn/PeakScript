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

bool ModulePool::AddModule(const std::string& moduleName, std::shared_ptr<Module> module, bool bExecuted) {
	auto ite = _modulesMap.find(moduleName);
	if (ite == _modulesMap.end()) {
		_modulesMap.emplace(moduleName, module);
		if (bExecuted) {
			_executedSet.emplace(moduleName);
		}
		return true;
	}
	return false;
}

void ModulePool::RemoveModule(const std::string& moduleName) {
	auto ite = _modulesMap.find(moduleName);
	if (ite != _modulesMap.end()) {
		_modulesMap.erase(ite);
	}
	auto eite = _executedSet.find(moduleName);
	if (eite != _executedSet.end()) {
		_executedSet.erase(eite);
	}
}

bool ModulePool::AddModuleFilename(const std::string& moduleName, const std::string& filename) {
	if (_moduleToFilesMap.find(moduleName) == _moduleToFilesMap.end()) {
		_moduleToFilesMap.emplace(moduleName, filename);
		return true;
	}
	return false;
}
const std::string& ModulePool::GetFilenameOfModule(const std::string& moduleName) const {
	auto ite = _moduleToFilesMap.find(moduleName);
	if (ite != _moduleToFilesMap.end()) {
		return ite->second;
	}
	static std::string EMPTY_STRING = "";
	return EMPTY_STRING;
}
std::shared_ptr<Module> ModulePool::UseModule(const std::string& moduleName) {
	std::shared_ptr<Module> ret{nullptr};
	do {
		auto ite = _modulesMap.find(moduleName);
		if (ite != _modulesMap.end()) {
			ret = ite->second;
			break;
		}

		std::shared_ptr<Executer> executer{nullptr};

		const auto& filename = GetFilenameOfModule(moduleName);
		executer = _CreateExecuter(filename);
		if (!executer) {
			executer = _CreateExecuter(moduleName);
		}

		if (!executer) {
			return nullptr;
		}
		ret = std::shared_ptr<Module>(new Module(moduleName, executer));
		_modulesMap.emplace(moduleName, ret);
	} while (false);

	bool bExecuted = IsExecuted(moduleName);

	if (!bExecuted) {
		if (ret->Execute()) {
			_executedSet.emplace(moduleName);
		} else {
			auto ite = _modulesMap.find(moduleName);
			if (ite != _modulesMap.end()) {
				_modulesMap.erase(ite);
			}
			ret = nullptr;
		}
	}

	return ret;
}

bool ModulePool::IsExecuted(const std::string& moduleName) const {
	return _executedSet.find(moduleName) != _executedSet.end();
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
