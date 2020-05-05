#include "SentenceExpressionValueArray.h"
#include "../Value/ValueArray.h"

using namespace peak::interpreter;

SentenceExpressionValueArray::SentenceExpressionValueArray(const std::vector<std::shared_ptr<SentenceExpression>>& valueExpressionArray)
	: SentenceExpressionValue(std::shared_ptr<Value>(new ValueArray())), _expressionArray(valueExpressionArray) {
}
ExecuteResult SentenceExpressionValueArray::Execute(std::shared_ptr<Space> space) {
	if (_expressionArray.empty()) {
		return ExecuteResult::Successed;
	}
	auto& arr = std::static_pointer_cast<ValueArray>(GetValue())->GetArray();
	arr.reserve(_expressionArray.size());
	for (auto i = 0u; i < _expressionArray.size(); ++i) {
		auto expression = _expressionArray[i];
		if (!IsSuccess(expression->Execute(space))) {
			return ExecuteResult::Failed;
		}
		auto value = expression->GetValue();
		arr.emplace_back(value);
	}
	return ExecuteResult::Successed;
}