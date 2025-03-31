#include "Space.h"
#include "BuiltInFunction.h"
#include "Module.h"
#include "ModulePool.h"
#include "Value/Value.h"
#include "Variable.h"
#include "Value/ValueTool.h"
#include "Value/ValueFunction.h"

using namespace peak::interpreter;

Space::Space(SpaceType spaceType)
	: _spaceType(spaceType) {
}
Space::Space(SpaceType spaceType, std::shared_ptr<Space> parent)
	: _spaceType(spaceType), _parent(parent) {
}

std::shared_ptr<Space> Space::CopySpace() const {
	std::shared_ptr<Space> parent{nullptr};
	if (_parent) {
		parent = _parent->CopySpace();
	}
	auto space = std::shared_ptr<Space>(new Space(_spaceType, parent));
	space->_spaceOfUsing = _spaceOfUsing;
	space->_importModules = _importModules;

	for (auto& pair : _variables) {
		auto tempVariable = pair.second;
		auto tempVlaue = tempVariable->GetValue();
		auto variable = std::shared_ptr<Variable>(
			new Variable(pair.first, tempVariable->GetAttribute(), tempVlaue ? tempVlaue->Clone() : nullptr));
		space->_variables.emplace(pair.first, variable);
	}
	return space;
}

void Space::Clear() {
	_variables.clear();
	_spaceOfUsing.clear();
	_importModules.clear();
	auto modulePool = ModulePool::GetInstance();
	for (auto& name : _exportModulesNameSet) {
		modulePool->RemoveModule(name);
	}
	_exportModulesNameSet.clear();
}

bool Space::UseModule(std::shared_ptr<Module> module) {
	if (!module) {
		return false;
	}
	if (_importModules.find(module->GetName()) != _importModules.end()) {
		ErrorLogger::LogRuntimeError(module->GetName());
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Space, "The module \"" + module->GetName() + "\" is exist!");
		return false;
	}
	_importModules.emplace(module->GetName(), module);
	return true;
}

bool Space::SetExportModule(const std::string& moduleName) {
	if (_exportModulesNameSet.find(moduleName) == _exportModulesNameSet.end()) {
		_exportModulesNameSet.emplace(moduleName);
		return true;
	}
	return false;
}

bool Space::AddVariable(std::shared_ptr<Variable> value) {
	if (!value) {
		return false;
	}
	auto findIte = _variables.find(value->GetName());
	if (findIte != _variables.end()) {
		if (ValueTool::IsFunction(findIte->second->GetValue()) && ValueTool::IsFunction(value->GetValue())) {
			if (std::static_pointer_cast<ValueFunction>(findIte->second->GetValue())->AddFunction(std::static_pointer_cast<ValueFunction>(value->GetValue()))) {
				return true;
			}
		}
		ErrorLogger::LogRuntimeError(value->GetName());
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Space, "The variable \"" + value->GetName() + "\" is exist!");
		return false;
	}
	_variables.emplace(value->GetName(), value);
	return true;
}

std::shared_ptr<Variable> Space::FindVariableFromTop(const std::string& name) const {
	auto ite = _variables.find(name);
	if (ite != _variables.end()) {
		return ite->second;
	}
	return nullptr;
}

std::shared_ptr<Variable> Space::FindVariable(const std::string& name) const {
	auto ite = _variables.find(name);
	if (ite != _variables.end()) {
		return ite->second;
	}
	for (auto space : _spaceOfUsing) {
		auto find = space->FindVariable(name);
		if (find) {
			return find;
		}
	}
	for (auto& pair : _importModules) {
		auto find = pair.second->GetSpace()->FindVariableFromTop(name);
		if (find) {
			return find;
		}
	}
	if (_parent) {
		return _parent->FindVariable(name);
	}
	return BuiltInFunction::GetInstance()->FindVariable(name);
}

SpaceType Space::GetSpaceType() const {
	return _spaceType;
}

void Space::AddSpaceOfUsing(std::shared_ptr<Space> space) {
	_spaceOfUsing.emplace_back(space);
}
