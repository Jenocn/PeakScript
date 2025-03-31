#include "ExpressionVariableAnalysisInstance.h"
#include "../../Value/ValueTool.h"
#include "../../Variable.h"
#include "../SentenceExpressionVariable.h"

using namespace peak::interpreter;

ExpressionVariableAnalysisName::ExpressionVariableAnalysisName(const std::string& name)
	: _name(name) {
}
std::shared_ptr<Variable> ExpressionVariableAnalysisName::Execute(std::shared_ptr<Space> space) {
	auto ret = space->FindVariable(_name);
	if (!ret) {
		ErrorLogger::LogRuntimeError(_name);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableNameAnalysis, "The variable \"" + _name + "\" not found!");
	}
	return ret;
}
void ExpressionVariableAnalysisName::SetName(const std::string& name) {
	_name = name;
}

ExpressionVariableAnalysisArrayItem::ExpressionVariableAnalysisArrayItem(std::shared_ptr<SentenceExpression> valueExpression, std::vector<std::shared_ptr<SentenceExpression>> indexExpressionVec)
	: _valueExpression(valueExpression), _indexExpressionVec(indexExpressionVec) {
}

std::shared_ptr<Variable> ExpressionVariableAnalysisArrayItem::Execute(std::shared_ptr<Space> space) {
	if (!Sentence::IsSuccess(_valueExpression->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableArrayItemAnalysis, "The expression execute failed!");
		return nullptr;
	}
	auto retValue = _valueExpression->GetValue();
	std::shared_ptr<Variable> retVariable{nullptr};

	auto expressionVecSize = _indexExpressionVec.size();
	for (auto i = 0u; i < expressionVecSize; ++i) {
		if (!ValueTool::IsArray(retValue)) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableArrayItemAnalysis, "The result of expression isn't a array!");
			return nullptr;
		}
		auto& arr = std::static_pointer_cast<ValueArray>(retValue)->GetArray();
		auto expression = _indexExpressionVec[i];
		if (!Sentence::IsSuccess(expression->Execute(space))) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableArrayItemAnalysis, "The expression execute failed!");
			return nullptr;
		}
		auto indexValue = expression->GetValue();
		if (!ValueTool::IsInteger(indexValue)) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableArrayItemAnalysis, "The index isn't a integer value!");
			return nullptr;
		}
		auto index = static_cast<std::size_t>(std::static_pointer_cast<ValueNumber>(indexValue)->GetValue());
		if (index >= arr.size()) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableArrayItemAnalysis, "The index out of range!");
			return nullptr;
		}
		retVariable = arr[index];
		if (!retVariable) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableArrayItemAnalysis, "The array value is invalid!");
			return nullptr;
		}
		retValue = retVariable->GetValue();
	}

	return retVariable;
}

ExpressionVariableAnalysisInside::ExpressionVariableAnalysisInside(std::shared_ptr<SentenceExpression> header, std::vector<std::shared_ptr<SentenceExpression>> insides)
	: _header(header), _insides(insides) {
}
std::shared_ptr<Variable> ExpressionVariableAnalysisInside::Execute(std::shared_ptr<Space> space) {
	if (!Sentence::IsSuccess(_header->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableInsideAnalysis, "The header expression execute failed!");
		return nullptr;
	}
	auto headerValue = _header->GetValue();
	if (!ValueTool::IsObject(headerValue)) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableInsideAnalysis, "The header expression isn't a object!");
		return nullptr;
	}
	auto tempValue = headerValue;
	std::shared_ptr<Variable> retVariable{nullptr};
	for (auto expression : _insides) {
		if (!ValueTool::IsObject(tempValue)) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableInsideAnalysis, "The expression isn't a object!");
			return nullptr;
		}
		auto objSpace = std::static_pointer_cast<ValueObject>(tempValue)->GetSpace();
		if (expression->GetExpressionType() != ExpressionType::Variable) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableInsideAnalysis, "The inside expression can't return a variable!");
			return nullptr;
		}
		if (!Sentence::IsSuccess(expression->Execute(objSpace))) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::VariableInsideAnalysis, "The inside expression execute failed!");
			return nullptr;
		}
		retVariable = std::static_pointer_cast<SentenceExpressionVariable>(expression)->GetVariable();
		tempValue = expression->GetValue();
	}
	return retVariable;
}