#include "ExpressionVariableAnalysisInstance.h"
#include "../../Value/ValueTool.h"
#include "../../Variable.h"

using namespace peak::interpreter;

ExpressionVariableAnalysisName::ExpressionVariableAnalysisName(const std::string& name)
	: _name(name) {
}
std::shared_ptr<Variable> ExpressionVariableAnalysisName::Execute(std::shared_ptr<Space> space) {
	return space->FindVariable(_name);
}
void ExpressionVariableAnalysisName::SetName(const std::string& name) {
	_name = name;
}

ExpressionVariableAnalysisArrayItem::ExpressionVariableAnalysisArrayItem(std::shared_ptr<SentenceExpression> valueExpression, std::vector<std::shared_ptr<SentenceExpression>> indexExpressionVec)
	: _valueExpression(valueExpression), _indexExpressionVec(indexExpressionVec) {
}

std::shared_ptr<Variable> ExpressionVariableAnalysisArrayItem::Execute(std::shared_ptr<Space> space) {
	if (_indexExpressionVec.empty()) {
		return nullptr;
	}
	if (!Sentence::IsSuccess(_valueExpression->Execute(space))) {
		return nullptr;
	}
	auto retValue = _valueExpression->GetValue();
	std::shared_ptr<Variable> retVariable{nullptr};

	auto expressionVecSize = _indexExpressionVec.size();
	for (auto i = 0u; i < expressionVecSize; ++i) {
		if (!ValueTool::IsArray(retValue)) {
			return nullptr;
		}
		auto& arr = std::static_pointer_cast<ValueArray>(retValue)->GetArray();
		auto expression = _indexExpressionVec[i];
		if (!Sentence::IsSuccess(expression->Execute(space))) {
			return nullptr;
		}
		auto indexValue = expression->GetValue();
		if (!ValueTool::IsInteger(indexValue)) {
			return nullptr;
		}
		auto index = static_cast<std::size_t>(std::static_pointer_cast<ValueNumber>(indexValue)->GetValue());
		if (index >= arr.size()) {
			return nullptr;
		}
		retVariable = arr[index];
		if (!retVariable) {
			return nullptr;
		}
		retValue = retVariable->GetValue();
	}

	return retVariable;
}