
#include "SentenceVarFromName.h"
#include "Variable.h"

using namespace peak::interpreter;

SentenceVarFromName::SentenceVarFromName(const std::string& name, const std::string& fromName)
	: _fromName(fromName) {
	_variable = std::shared_ptr<Variable>(new Variable(name));
}

bool SentenceVarFromName::Execute(std::shared_ptr<Space> space) {
	auto fromValue = space->FindVariable(_variable->GetName());
	if (!fromValue) {
		return false;
	}
	_variable->SetValue(fromValue->GetValue());
	return space->AddVariable(_variable);
}