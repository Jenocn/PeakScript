
#include "SentenceVarFromValue.h"
#include "Value.h"
#include "Variable.h"

using namespace peak::interpreter;

SentenceVarFromValue::SentenceVarFromValue(const std::string& name, std::shared_ptr<Value> fromValue) {
	_variable = std::shared_ptr<Variable>(new Variable(name));
	_variable->SetValue(fromValue);
}

bool SentenceVarFromValue::Execute(std::shared_ptr<Space> space) {
	return space->AddVariable(_variable);
}