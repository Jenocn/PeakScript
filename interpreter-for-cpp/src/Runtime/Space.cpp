#include "Space.h"
#include "ClassTemplate.h"
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
	for (auto space : _spaceOfUsing) {
		auto find = space->FindVariable(name);
		if (find) {
			return find;
		}
	}
	return nullptr;
}

bool Space::AddClassTemplate(std::shared_ptr<ClassTemplate> classTemplate) {
	if (!classTemplate) {
		return false;
	}
	if (_classTemplates.find(classTemplate->GetName()) != _classTemplates.end()) {
		return false;
	}
	_classTemplates.emplace(classTemplate->GetName(), classTemplate);
	return true;
}
std::shared_ptr<ClassTemplate> Space::FindClassTemplate(const std::string& name) const {
	auto ite = _classTemplates.find(name);
	if (ite != _classTemplates.end()) {
		return ite->second;
	}
	if (_parent) {
		return _parent->FindClassTemplate(name);
	}
	for (auto space : _spaceOfUsing) {
		auto find = space->FindClassTemplate(name);
		if (find) {
			return find;
		}
	}
	return nullptr;
}

SpaceType Space::GetSpaceType() const {
	return _spaceType;
}

std::shared_ptr<Space> Space::CopySpace() const {
	auto space = std::shared_ptr<Space>(new Space(_spaceType, _parent ? _parent->CopySpace() : nullptr));
	for (auto v : _spaceOfUsing) {
		space->AddSpaceOfUsing(v->CopySpace());
	}
	for (auto& pair : _variables) {
		auto v = pair.second;
		auto nv = std::shared_ptr<Variable>(new Variable(pair.first, v->GetAttribute(), v->GetValue()));
		space->AddVariable(nv);
	}
	for (auto& pair : _classTemplates) {
		space->AddClassTemplate(pair.second);
	}
	return space;
}

void Space::AddSpaceOfUsing(std::shared_ptr<Space> space) {
	_spaceOfUsing.emplace_back(space);
}
