/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace peak::interpreter {

class Variable;

enum class SpaceType {
	None,
	Condition,
	Loop,
	Function,
};

class Space {
public:
	Space(SpaceType spaceType);
	Space(SpaceType spaceType, std::shared_ptr<Space> parent);

	void Clear();

	bool AddVariable(std::shared_ptr<Variable> value);

	std::shared_ptr<Variable> FindVariable(const std::string& name) const;

	SpaceType GetSpaceType() const;

private:
	SpaceType _spaceType{SpaceType::None};
	std::shared_ptr<Space> _parent{nullptr};

	std::unordered_map<std::string, std::shared_ptr<Variable>> _variables;
};
} // namespace peak::interpreter