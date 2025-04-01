#include "sentence_return.h"
#include "sentence_expression.h"

using namespace peak;

SentenceReturn::SentenceReturn() {
}

SentenceReturn::SentenceReturn(std::shared_ptr<SentenceExpression> expression)
	: _returnExpression(expression) {
}
ExecuteResult SentenceReturn::Execute(std::shared_ptr<Space> space) {
	if (!IsSuccess(_returnExpression->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Return, "The expression execute failed!");
		return ExecuteResult::Failed;
	}
	SetReturnValue(_returnExpression->GetValue());
	return ExecuteResult::Return;
}

std::shared_ptr<Value> SentenceReturn::GetReturnValue() const {
	return _returnValue;
}

void SentenceReturn::SetReturnValue(std::shared_ptr<Value> value) {
	_returnValue = value;
}
