#include "ClassTemplate.h"
#include "Space.h"

using namespace peak::interpreter;

ClassTemplate::ClassTemplate(const std::string& name, std::shared_ptr<ClassTemplate> parent, std::shared_ptr<Space> spacePrivate, std::shared_ptr<Space> spacePublic)
	: _name(name), _parent(parent), _spacePrivate(spacePrivate), _spacePublic(spacePublic) {
	_spaceOfThis = std::shared_ptr<Space>(new Space(SpaceType::None));
	_spaceOfThis->AddSpaceOfUsing(_spacePrivate);
	_spaceOfThis->AddSpaceOfUsing(_spacePublic);
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

std::shared_ptr<Space> ClassTemplate::GetSpaceOfThis() const {
	return _spaceOfThis;
}

std::shared_ptr<ClassTemplate> ClassTemplate::Clone() const {
	return std::shared_ptr<ClassTemplate>(new ClassTemplate(_name, _parent ? _parent->Clone() : nullptr, _spacePrivate->Clone(), _spacePublic->Clone()));
}

std::shared_ptr<ClassTemplate> ClassTemplate::GetParent() const {
	return _parent;
}
