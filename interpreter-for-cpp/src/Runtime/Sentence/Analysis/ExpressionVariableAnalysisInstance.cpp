#include "ExpressionVariableAnalysisInstance.h"
#include "../../Value/ValueTool.h"

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

ExpressionVariableAnalysisArrayItem::ExpressionVariableAnalysisArrayItem(std::shared_ptr<Value> valueArray, std::shared_ptr<SentenceExpression> indexExpression)
: _valueArray(valueArray), _indexExpression(indexExpression) {
}
std::shared_ptr<Variable> ExpressionVariableAnalysisArrayItem::Execute(std::shared_ptr<Space> space) {
	if (!Sentence::IsSuccess(_indexExpression->Execute(space))) {
		return nullptr;
	}
	auto indexValue = _indexExpression->GetValue();
	if (ValueTool::IsArray(_valueArray)) {
		if (!ValueTool::IsInteger(indexValue)) {
			return nullptr;
		}
		auto index = static_cast<std::size_t>(std::static_pointer_cast<ValueNumber>(indexValue)->GetValue());
		auto& arr = std::static_pointer_cast<ValueArray>(_valueArray)->GetArray();
		if (index < arr.size()) {
			return arr[index];
		}
		return nullptr;
	}
	return nullptr;
}