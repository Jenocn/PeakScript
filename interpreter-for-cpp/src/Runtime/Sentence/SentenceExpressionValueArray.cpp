#include "SentenceExpressionValueArray.h"
#include "../Value/ValueArray.h"

using namespace peak::interpreter;

SentenceExpressionValueArray::SentenceExpressionValueArray(const std::vector<std::shared_ptr<SentenceExpression>>& valueExpressionArray)
	: _expressionArray(valueExpressionArray) {
}
ExecuteResult SentenceExpressionValueArray::Execute(std::shared_ptr<Space> space) {
	auto valueArray = std::shared_ptr<ValueArray>(new ValueArray());
	if (!_expressionArray.empty()) {
		valueArray->Reserve(_expressionArray.size());
		for (auto i = 0u; i < _expressionArray.size(); ++i) {
			auto expression = _expressionArray[i];
			if (!IsSuccess(expression->Execute(space))) {
				ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Array, "The array execute failed!");
				return ExecuteResult::Failed;
			}
			auto value = expression->GetValue();
			valueArray->EmplaceBack(value);
		}
	}
	SetValue(valueArray);
	return ExecuteResult::Successed;
}