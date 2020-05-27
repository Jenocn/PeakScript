/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Base/CommonInclude.h"
#include "../Base/ErrorLogger.h"

namespace peak {
namespace interpreter {

class Variable;

enum class SpaceType {
	None,
	Condition,
	Loop,
	Function,
	Object,
};

class Space {
public:
	Space(SpaceType spaceType);
	Space(SpaceType spaceType, std::shared_ptr<Space> parent);

public:
	std::shared_ptr<Space> CopySpace() const;
	void Clear();

	bool AddVariable(std::shared_ptr<Variable> value);
	std::shared_ptr<Variable> FindVariable(const std::string& name) const;
	std::shared_ptr<Variable> FindVariableFromTop(const std::string& name) const;

	SpaceType GetSpaceType() const;

public:
	void AddSpaceOfUsing(std::shared_ptr<Space> space);

private:
	SpaceType _spaceType{SpaceType::None};
	std::shared_ptr<Space> _parent{nullptr};

	std::list<std::shared_ptr<Space>> _spaceOfUsing;

	std::unordered_map<std::string, std::shared_ptr<Variable>> _variables;
};
} // namespace interpreter
} // namespace peak