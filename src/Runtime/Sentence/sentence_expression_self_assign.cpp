#include "SentenceExpressionSelfAssign.h"
#include "../Value/IValueCalculate.h"
#include "../Variable.h"
#include "SentenceExpressionVariable.h"

using namespace peak::interpreter;
ExecuteResult SentenceExpressionSelfAssign::Execute(std::shared_ptr<Space> space) {
	if (_left->GetExpressionType() != ExpressionType::Variable) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::SelfAssign, "The expression target isn't a variable!");
		return ExecuteResult::Failed;
	}

	if (!IsSuccess(SentenceExpressionMath::Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::SelfAssign, "The [self-assign-expression] execute failed!");
		return ExecuteResult::Failed;
	}

	auto temp = std::static_pointer_cast<SentenceExpressionVariable>(_left);
	auto variable = temp->GetVariable();
	if (!variable) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::SelfAssign, "The [self-assign-expression] execute failed!");
		return ExecuteResult::Failed;
	}

	if (!variable->SetValue(GetValue())) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::SelfAssign, "The [self-assign-expression] execute failed!");
		return ExecuteResult::Failed;
	}

	return ExecuteResult::Successed;
}