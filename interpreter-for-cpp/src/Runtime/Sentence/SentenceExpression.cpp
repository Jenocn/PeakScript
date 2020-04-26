#include "SentenceExpression.h"
#include "Sentence.h"
#include "../Value/Value.h"

using namespace peak::interpreter;

std::shared_ptr<Value> SentenceExpression::GetValue() const {
	return _value;
}

void SentenceExpression::SetValue(std::shared_ptr<Value> value) {
	_value = value;
}
