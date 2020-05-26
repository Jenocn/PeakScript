#include "SentenceVariableSet.h"
#include "../Variable.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceVariableSet::SentenceVariableSet(const std::string& name, std::shared_ptr<SentenceExpression> expression)
	: _name(name), _expression(expression) {
}

ExecuteResult SentenceVariableSet::Execute(std::shared_ptr<Space> space) {
	auto variable = space->FindVariable(_name);
	if (!variable) {
		variable = std::shared_ptr<Variable>(new Variable(_name, VariableAttribute::None));
		space->AddVariable(variable);
	}
	if (_expression) {
		if (!IsSuccess(_expression->Execute(space))) {
			ErrorLogger::LogRuntimeError(_name);
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableSet, "The \"" + _name + "\" expression execute failed!");
			return ExecuteResult::Failed;
		}
		if (!variable->SetValue(_expression->GetValue())) {
			ErrorLogger::LogRuntimeError(_name);
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableSet, "The \"" + _name + "\" expression execute failed!");
			return ExecuteResult::Failed;
		}
	}
	return ExecuteResult::Successed;
}
