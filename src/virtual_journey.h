/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Base/CommonInclude.h"

namespace peak {

namespace interpreter {
class Variable;
class Executer;
class Space;
class Value;
} // namespace interpreter

class VirtualJourney {
public:
	VirtualJourney(std::shared_ptr<interpreter::Executer> executer);
	bool Execute();
	std::shared_ptr<interpreter::Space> GetSpace() const;

public:
	std::shared_ptr<interpreter::Variable> FindVariable(const std::string& name) const;
	bool AddVariable(std::shared_ptr<interpreter::Variable> variable);

	std::shared_ptr<interpreter::Value> ExecuteFunction(const std::string& name, const std::vector<std::shared_ptr<interpreter::Value>>& args);
	std::shared_ptr<interpreter::Value> ExecuteFunction(const std::string& name);

private:
	std::shared_ptr<interpreter::Executer> _executer{nullptr};
};
} // namespace peak