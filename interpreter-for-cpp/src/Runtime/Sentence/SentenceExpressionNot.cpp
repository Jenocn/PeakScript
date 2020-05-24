#include "SentenceExpressionNot.h"
#include "../Value/ValueTool.h"

using namespace peak::interpreter;

SentenceExpressionNot::SentenceExpressionNot(std::shared_ptr<SentenceExpression> expression)
	: _expression(expression) {
}
ExecuteResult SentenceExpressionNot::Execute(std::shared_ptr<Space> space) {
	if (!IsSuccess(_expression->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ExpressionNot, "The [not-expression] execute failed!");
		return ExecuteResult::Failed;
	}

	auto ret = ValueTool::ToLogic(_expression->GetValue());
	SetValue(std::shared_ptr<Value>(new ValueBool(!ret)));

	return ExecuteResult::Successed;
}
