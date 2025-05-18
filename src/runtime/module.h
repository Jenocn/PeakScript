/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "base/error_logger.h"

namespace peak {

class Executer;
class Space;

class Module {
public:
	Module(std::shared_ptr<Executer> executer);
	Module(std::shared_ptr<Space> space);
	bool Execute();

	bool IsExecuted() const;

	std::shared_ptr<Space> GetSpace() const;

private:
	std::shared_ptr<Executer> _executer { nullptr };
	std::shared_ptr<Space> _space { nullptr };
	bool _bExecuted { false };
};

} // namespace peak