#include "Space.h"
#include "Value.h"
#include "Variable.h"
#include "Method.h"

using namespace peak::interpreter;

Space::Space() {
}
Space::Space(std::shared_ptr<Space> parent) {
	_parent = parent;
}

void Space::Clear() {
	_variables.clear();
	_methods.clear();
}

bool Space::AddVariable(std::shared_ptr<Variable> value) {
	if (!value) { return false; }
	if (_variables.find(value->GetName()) != _variables.end()) {
		return false;
	}
	_variables.emplace(value->GetName(), value);
	return true;
}
bool Space::AddMethod(std::shared_ptr<Method> value) {
	if (_methods.find(value->GetName()) != _methods.end()) {
		return false;
	}
	_methods.emplace(value->GetName(), value);
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
std::shared_ptr<Method> Space::FindMethod(const std::string& name) const {
	auto ite = _methods.find(name);
	if (ite != _methods.end()) {
		return ite->second;
	}
	if (_parent) {
		return _parent->FindMethod(name);
	}
	return nullptr;
}