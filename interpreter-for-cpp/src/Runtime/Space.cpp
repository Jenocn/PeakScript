#include "Space.h"
#include "System.h"
#include "Value/Value.h"
#include "Variable.h"

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

	for (auto& pair : _variables) {
		auto tempVariable = pair.second;
		auto tempVlaue = tempVariable->GetValue();
		auto variable = std::shared_ptr<Variable>(new Variable(pair.first, tempVariable->GetAttribute()));
		if (tempVlaue) {
			variable->SetValue(tempVlaue->Clone());
		}
		space->_variables.emplace(pair.first, variable);
	}
	return space;
}

void Space::Clear() {
	_variables.clear();
}

bool Space::AddVariable(std::shared_ptr<Variable> value) {
	if (!value) {
		return false;
	}
	if (_variables.find(value->GetName()) != _variables.end()) {
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
	if (_parent) {
		return _parent->FindVariable(name);
	}
	return System::FindVariable(name);
}

SpaceType Space::GetSpaceType() const {
	return _spaceType;
}

void Space::AddSpaceOfUsing(std::shared_ptr<Space> space) {
	_spaceOfUsing.emplace_back(space);
}
