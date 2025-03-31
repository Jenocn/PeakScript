#include "Module.h"
#include "Executer.h"

using namespace peak::interpreter;

Module::Module(const std::string& name, std::shared_ptr<Executer> executer)
	: _name(name),
	  _executer(executer) {
	_space = _executer->GetSpace();
}
Module::Module(const std::string& name, std::shared_ptr<Space> space)
	: _name(name),
	  _space(space),
	  _bExecuted(true) {
}

bool Module::Execute() {
	_bExecuted = true;
	if (_executer) {
		return _executer->Execute();
	}
	return true;
}

const std::string& Module::GetName() const {
	return _name;
}

bool Module::IsExecuted() const {
	return _bExecuted;
}

std::shared_ptr<Space> Module::GetSpace() const {
	return _space;
}
