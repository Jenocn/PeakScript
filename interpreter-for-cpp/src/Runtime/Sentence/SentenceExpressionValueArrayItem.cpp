#include "SentenceExpressionValueArrayItem.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceExpressionValueArrayItem::SentenceExpressionValueArrayItem(std::shared_ptr<SentenceExpression> sentenceExpression, const std::vector<std::shared_ptr<SentenceExpression>>& indexExpressionVec)
	: _sentenceExpression(sentenceExpression), _indexExpressionVec(indexExpressionVec) {
}

ExecuteResult SentenceExpressionValueArrayItem::Execute(std::shared_ptr<Space> space) {
	if (_indexExpressionVec.empty()) {
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_sentenceExpression->Execute(space))) {
		return ExecuteResult::Failed;
	}
	auto retValue = _sentenceExpression->GetValue();

	auto expressionVecSize = _indexExpressionVec.size();
	for (auto i = 0u; i < expressionVecSize; ++i) {
		if (!ValueTool::IsArray(retValue)) {
			return ExecuteResult::Failed;
		}
		auto& arr = std::static_pointer_cast<ValueArray>(retValue)->GetArray();
		auto expression = _indexExpressionVec[i];
		if (!IsSuccess(expression->Execute(space))) {
			return ExecuteResult::Failed;
		}
		auto indexValue = expression->GetValue();
		if (!ValueTool::IsInteger(indexValue)) {
			return ExecuteResult::Failed;
		}
		auto index = static_cast<std::size_t>(std::static_pointer_cast<ValueNumber>(indexValue)->GetValue());
		if (index >= arr.size()) {
			return ExecuteResult::Failed;
		}
		retValue = arr[index]->GetValue();
	}

	SetValue(retValue);
	return ExecuteResult::Successed;
}

