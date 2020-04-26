#include "SentenceReturn.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceReturn::SentenceReturn() {
}

SentenceReturn::SentenceReturn(std::shared_ptr<SentenceExpression> expression)
	: _expression(expression) {
}
ExecuteResult SentenceReturn::Execute(std::shared_ptr<Space> space) {
	if (!_expression || !IsSuccess(_expression->Execute(space))) {
		return ExecuteResult::Failed;
	}
	SetReturnValue(_expression->GetValue());
	return ExecuteResult::Return;
}

std::shared_ptr<Value> SentenceReturn::GetReturnValue() const {
	return _returnValue;
}

void SentenceReturn::SetReturnValue(std::shared_ptr<Value> value) {
	_returnValue = value;
}
