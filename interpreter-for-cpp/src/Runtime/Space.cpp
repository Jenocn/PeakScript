#include "Space.h"
#include "Value/Value.h"
#include "Variable.h"

using namespace peak::interpreter;

Space::Space(SpaceType spaceType)
	: _spaceType(spaceType) {
}
Space::Space(SpaceType spaceType, std::shared_ptr<Space> parent)
	: _spaceType(spaceType), _parent(parent) {
}

void Space::Clear() {
	_variables.clear();
}

bool Space::AddVariable(std::shared_ptr<Variable> value) {
	if (!value) {
		return false;
	}
	if (_variables.find(value->GetName()) != _variables.end()) {
		return false;
	}
	_variables.emplace(value->GetName(), value);
	return true;
}

std::shared_ptr<Variable> Space::FindVariable(const std::string& name) const {
	auto ite = _variables.find(name);
	if (ite != _variables.end()) {
		return ite->second;
	}
	if (_parent) {
		return _parent->FindVariable(name);
	}
	return nullptr;
}

SpaceType Space::GetSpaceType() const {
	return _spaceType;
}
