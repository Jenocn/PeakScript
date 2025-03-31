#include "SentenceExpressionVariable.h"
#include "../Variable.h"
#include "Analysis/IExpressionVariableAnalysis.h"

using namespace peak::interpreter;

SentenceExpressionVariable::SentenceExpressionVariable(std::shared_ptr<IExpressionVariableAnalysis> variableAnalysis)
	: _analysis(variableAnalysis) {
}

ExecuteResult SentenceExpressionVariable::Execute(std::shared_ptr<Space> space) {
	_variable = _analysis->Execute(space);
	if (!_variable) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ExpressionVariable, "The variable-expression execute failed!");
		return ExecuteResult::Failed;
	}
	SetValue(_variable->GetValue());
	return ExecuteResult::Successed;
}

std::shared_ptr<Variable> SentenceExpressionVariable::GetVariable() const {
	return _variable;
}
