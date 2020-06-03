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
} // namespace interpreter

class VirtualJourney {
public:
	VirtualJourney(std::shared_ptr<interpreter::Executer> executer);

	bool Execute();

public:
	std::shared_ptr<interpreter::Variable> FindVariable(const std::string& name);
	bool AddVariable(std::shared_ptr<interpreter::Variable> variable);

private:
	std::shared_ptr<interpreter::Executer> _executer{nullptr};
};
} // namespace peak