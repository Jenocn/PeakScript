#include "SentenceExpressionValueArray.h"
#include "../Value/ValueArray.h"

using namespace peak::interpreter;

SentenceExpressionValueArray::SentenceExpressionValueArray(const std::vector<std::shared_ptr<SentenceExpression>>& valueExpressionArray)
	: _expressionArray(valueExpressionArray) {
}
ExecuteResult SentenceExpressionValueArray::Execute(std::shared_ptr<Space> space) {
	if (_expressionArray.empty()) {
		return ExecuteResult::Successed;
	}

	auto valueArray = std::shared_ptr<ValueArray>(new ValueArray());
	valueArray->Reserve(_expressionArray.size());
	for (auto i = 0u; i < _expressionArray.size(); ++i) {
		auto expression = _expressionArray[i];
		if (!IsSuccess(expression->Execute(space))) {
			return ExecuteResult::Failed;
		}
		auto value = expression->GetValue();
		valueArray->EmplaceBack(value);
	}
	SetValue(valueArray);
	return ExecuteResult::Successed;
}