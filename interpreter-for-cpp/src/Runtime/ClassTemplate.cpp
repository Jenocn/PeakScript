#include "ClassTemplate.h"
#include "Space.h"

using namespace peak::interpreter;

ClassTemplate::ClassTemplate(const std::string& name, std::shared_ptr<ClassTemplate> parent, std::shared_ptr<Space> spacePrivate, std::shared_ptr<Space> spacePublic, std::shared_ptr<Space> spaceStatic)
	: _name(name), _parent(parent), _spacePrivate(spacePrivate), _spacePublic(spacePublic), _spaceStatic(spaceStatic) {
}

const std::string& ClassTemplate::GetName() const {
	return _name;
}

std::shared_ptr<Variable> ClassTemplate::FindPublicVariable(const std::string& name) const {
	auto variable = _spacePublic->FindVariable(name);
	if (!variable && _parent) {
		variable = _parent->FindPublicVariable(name);
	}
	return variable;
}

std::shared_ptr<Variable> ClassTemplate::FindPrivateVariable(const std::string& name) const {
	return _spacePrivate->FindVariable(name);
}

std::shared_ptr<Space> ClassTemplate::GetPublicSpace() const {
	return _spacePublic;
}
std::shared_ptr<Space> ClassTemplate::GetPrivateSpace() const {
	return _spacePrivate;
}

std::shared_ptr<Space> ClassTemplate::GetSpaceOfThis() const {
	return _spaceOfThis;
}
std::shared_ptr<Space> ClassTemplate::GetStaticSpace() const {
	return _spaceStatic;
}
std::shared_ptr<ClassTemplate> ClassTemplate::CreateInstance() const {
	auto instance = std::shared_ptr<ClassTemplate>(new ClassTemplate(_name, _parent ? _parent->CreateInstance() : nullptr, _spacePrivate->CopySpace(), _spacePublic->CopySpace(), _spaceStatic));
	instance->_spaceOfThis = std::shared_ptr<Space>(new Space(SpaceType::None));
	instance->_spaceOfThis->AddSpaceOfUsing(instance->_spacePrivate);
	instance->_spaceOfThis->AddSpaceOfUsing(instance->_spacePublic);
	instance->_spaceOfThis->AddClassTemplate(instance);
	return instance;
}

std::shared_ptr<ClassTemplate> ClassTemplate::GetParent() const {
	return _parent;
}
