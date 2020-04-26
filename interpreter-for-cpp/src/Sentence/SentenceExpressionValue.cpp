#include "SentenceExpressionValue.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceExpressionValue::SentenceExpressionValue(std::shared_ptr<Value> value)
	: _value(value) {
}

ExecuteResult SentenceExpressionValue::Execute(std::shared_ptr<Space> space) {
	if (!_value) {
		return ExecuteResult::Failed;
	}
	SetValue(_value);
	return ExecuteResult::Successed;
}
