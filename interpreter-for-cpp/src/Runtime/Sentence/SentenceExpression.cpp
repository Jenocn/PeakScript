#include "SentenceExpression.h"
#include "../Value/Value.h"
#include "Sentence.h"

using namespace peak::interpreter;

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

ExecuteResult SentenceExpression::Execute(std::shared_ptr<Space> space) {
	if (!_value) {
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}
