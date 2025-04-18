#include "sentence_expression.h"
#include "runtime/value/value.h"

using namespace peak;

SentenceExpression::SentenceExpression()
	: _value(nullptr) {
}
SentenceExpression::SentenceExpression(std::shared_ptr<Value> value)
	: _value(value) {
}

std::shared_ptr<Value> SentenceExpression::GetValue() const {
	return _value;
}

void SentenceExpression::SetValue(std::shared_ptr<Value> value) {
	_value = value;
}

ExecuteResult SentenceExpression::Execute(std::shared_ptr<Space>) {
	if (!_value) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Expression, "The value is null!");
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}
