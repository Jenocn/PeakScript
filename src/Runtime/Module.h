/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../Base/CommonInclude.h"

namespace peak {
namespace interpreter {

class Executer;
class Space;

class Module {
public:
	Module(const std::string& name, std::shared_ptr<Executer> executer);
	Module(const std::string& name, std::shared_ptr<Space> space);
	bool Execute();

	const std::string& GetName() const;
	bool IsExecuted() const;

	std::shared_ptr<Space> GetSpace() const;

private:
	std::string _name;
	std::shared_ptr<Executer> _executer{nullptr};
	std::shared_ptr<Space> _space{nullptr};
	bool _bExecuted{false};
};

} // namespace interpreter
} // namespace peak