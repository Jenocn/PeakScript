#include "VirtualJourney.h"
#include "Runtime/Executer.h"

using namespace peak;
using namespace peak::interpreter;

VirtualJourney::VirtualJourney(std::shared_ptr<Executer> executer)
	: _executer(executer) {
}

bool VirtualJourney::Execute() {
	return _executer->Execute();
}

std::shared_ptr<Variable> VirtualJourney::FindVariable(const std::string& name) {
	return _executer->FindVariable(name);
}
bool VirtualJourney::AddVariable(std::shared_ptr<Variable> variable) {
	return _executer->AddVariable(variable);
}