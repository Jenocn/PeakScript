#include "SentenceExpressionValue.h"
#include "Variable.h"

using namespace peak::interpreter;

SentenceExpressionValue::SentenceExpressionValue(std::shared_ptr<Value> value)
	: _value(value) {
}

bool SentenceExpressionValue::Execute(std::shared_ptr<Space> space) {
	SetValue(_value);
	return true;
}
