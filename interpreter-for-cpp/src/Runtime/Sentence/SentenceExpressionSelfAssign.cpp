#include "SentenceExpressionSelfAssign.h"
#include "../Value/IValueCalculate.h"
#include "../Variable.h"
#include "SentenceExpressionVariable.h"

using namespace peak::interpreter;
ExecuteResult SentenceExpressionSelfAssign::Execute(std::shared_ptr<Space> space) {
	if (_left->GetExpressionType() != ExpressionType::Variable) {
		return ExecuteResult::Failed;
	}

	if (!IsSuccess(SentenceExpressionMath::Execute(space))) {
		return ExecuteResult::Failed;
	}

	auto temp = std::static_pointer_cast<SentenceExpressionVariable>(_left);
	auto variable = space->FindVariable(temp->GetVariableName());
	if (!variable) {
		return ExecuteResult::Failed;
	}

	if (!variable->SetValue(GetValue())) {
		return ExecuteResult::Failed;
	}

	return ExecuteResult::Successed;
}