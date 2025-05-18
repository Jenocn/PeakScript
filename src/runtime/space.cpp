#include "space.h"
#include "builtin/builtin_function.h"
#include "module.h"
#include "module_pool.h"
#include "value/value.h"
#include "variable.h"
#include "value/value_tool.h"

using namespace peak;

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
	auto space = std::make_shared<Space>(_spaceType, parent);
	space->_spaceOfUsing = _spaceOfUsing;

	for (auto& pair : _variables) {
		space->_variables.emplace(pair.first, pair.second->Clone());
	}
	return space;
}

void Space::Clear() {
	_variables.clear();
	_spaceOfUsing.clear();
}

bool Space::AddVariable(std::shared_ptr<Variable> value) {
	if (!value) {
		return false;
	}
	auto findIte = _variables.find(value->GetName());
	if (findIte != _variables.end()) {
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
	if (_parent) {
		auto ret = _parent->FindVariable(name);
		if (ret) {
			return ret;
		}
	}
	for (auto space : _spaceOfUsing) {
		auto find = space->FindVariable(name);
		if (find) {
			return find;
		}
	}
	return BuiltInFunction::GetInstance()->FindVariable(name);
}

SpaceType Space::GetSpaceType() const {
	return _spaceType;
}

std::unordered_map<std::string, std::shared_ptr<Variable>>& Space::GetVariables() {
	return _variables;
}

void Space::AddSpaceOfUsing(std::shared_ptr<Space> space) {
	_spaceOfUsing.emplace_back(space);
}
