/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "base/error_logger.h"

namespace peak {


class Variable;
class Executer;
class Space;
class Value;


class VirtualJourney {
public:
	VirtualJourney(std::shared_ptr<Executer> executer);
	bool Execute();
	std::shared_ptr<Space> GetSpace() const;

public:
	std::shared_ptr<Variable> FindVariable(const std::string& name) const;
	bool AddVariable(std::shared_ptr<Variable> variable);

	std::shared_ptr<Value> ExecuteFunction(const std::string& name, const std::vector<std::shared_ptr<Value>>& args);
	std::shared_ptr<Value> ExecuteFunction(const std::string& name);

private:
	std::shared_ptr<Executer> _executer{nullptr};
};
} // namespace peak