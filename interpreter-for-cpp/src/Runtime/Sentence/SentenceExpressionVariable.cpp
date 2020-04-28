#include "SentenceExpressionVariable.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceExpressionVariable::SentenceExpressionVariable(const std::string& name)
	: _name(name) {
}

ExecuteResult SentenceExpressionVariable::Execute(std::shared_ptr<Space> space) {
	auto findVariable = space->FindVariable(_name);
	if (!findVariable) {
		return ExecuteResult::Failed;
	}
	SetValue(findVariable->GetValue());
	return ExecuteResult::Successed;
}
