#include "sentence_foreach.h"
#include "runtime/value/value_tool.h"
#include "runtime/variable.h"
#include "sentence_expression.h"

using namespace peak;

SentenceForeach::SentenceForeach(const std::string& name, std::shared_ptr<SentenceExpression> expression, std::shared_ptr<Sentence> sentence)
	: _name(name), _expression(expression), _sentence(sentence) {
}
ExecuteResult SentenceForeach::Execute(std::shared_ptr<Space> space) {
	if (!IsSuccess(_expression->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Foreach, "The expression execute failed!");
		return ExecuteResult::Failed;
	}
	if (!ValueTool::IsArray(_expression->GetValue())) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Foreach, "The expression isn't a array!");
		return ExecuteResult::Failed;
	}
	auto& arr = std::static_pointer_cast<ValueArray>(_expression->GetValue())->GetArray();
	if (arr.empty()) {
		return ExecuteResult::Successed;
	}

	auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Loop, space));
	auto itemVariable = std::shared_ptr<Variable>(new Variable(_name, VariableAttribute::None));
	if (!tempSpace->AddVariable(itemVariable)) {
		ErrorLogger::LogRuntimeError(_name);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Foreach, "The variable \"" + _name + "\" execute failed!");
		return ExecuteResult::Failed;
	}
	auto contentSpace = std::shared_ptr<Space>(new Space(SpaceType::Loop, tempSpace));
	for (auto item : arr) {
		itemVariable->SetValue(item->GetValue());
		contentSpace->Clear();
		auto ret = _sentence->Execute(contentSpace);
		if (!IsSuccess(ret)) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Foreach, "The sentence execute failed!");
			return ExecuteResult::Failed;
		}
		if (ret == ExecuteResult::Break) {
			break;
		}
		if (ret == ExecuteResult::Return) {
			SetReturnValue(std::static_pointer_cast<SentenceReturn>(_sentence)->GetReturnValue());
			tempSpace->Clear();
			return ExecuteResult::Return;
		}
	}
	tempSpace->Clear();
	return ExecuteResult::Successed;
}