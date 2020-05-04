#include "SentenceExpressionValue.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceExpressionValue::SentenceExpressionValue(std::shared_ptr<Value> value)
	: SentenceExpression(value) {
}

ExecuteResult SentenceExpressionValue::Execute(std::shared_ptr<Space> space) {
	if (!GetValue()) {
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}
