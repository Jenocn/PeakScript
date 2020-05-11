#include "SentenceExpressionValueArray.h"
#include "../Value/ValueArray.h"

using namespace peak::interpreter;

SentenceExpressionValueArray::SentenceExpressionValueArray(const std::vector<std::shared_ptr<SentenceExpression>>& valueExpressionArray)
	: SentenceExpression(std::shared_ptr<Value>(new ValueArray())), _expressionArray(valueExpressionArray) {
}
ExecuteResult SentenceExpressionValueArray::Execute(std::shared_ptr<Space> space) {
	if (_expressionArray.empty()) {
		return ExecuteResult::Successed;
	}
	auto valueArray = std::static_pointer_cast<ValueArray>(GetValue());
	valueArray->Reserve(_expressionArray.size());
	for (auto i = 0u; i < _expressionArray.size(); ++i) {
		auto expression = _expressionArray[i];
		if (!IsSuccess(expression->Execute(space))) {
			return ExecuteResult::Failed;
		}
		auto value = expression->GetValue();
		valueArray->EmplaceBack(value);
	}
	return ExecuteResult::Successed;
}