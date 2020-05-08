/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <memory>
#include <string>

namespace peak::interpreter {

class Space;
class Variable;
class ValueFunction;

class ClassTemplate {
public:
	ClassTemplate(const std::string& name, std::shared_ptr<ClassTemplate> parent, std::shared_ptr<Space> spacePrivate, std::shared_ptr<Space> spacePublic);
	const std::string& GetName() const;

	std::shared_ptr<Variable> FindPublicVariable(const std::string& name) const;
	std::shared_ptr<Variable> FindPrivateVariable(const std::string& name) const;

	std::shared_ptr<Space> GetSpaceOfThis() const;

	std::shared_ptr<ClassTemplate> Clone() const;

private:
	std::string _name;
	std::shared_ptr<ClassTemplate> _parent{nullptr};
	std::shared_ptr<Space> _spacePrivate{nullptr};
	std::shared_ptr<Space> _spacePublic{nullptr};
	std::shared_ptr<Space> _spaceOfThis{nullptr};
};
} // namespace peak::interpreter