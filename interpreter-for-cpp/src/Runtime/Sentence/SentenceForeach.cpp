#include "SentenceForeach.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceForeach::SentenceForeach(const std::string& name, std::shared_ptr<SentenceExpression> expression, std::shared_ptr<Sentence> sentence)
	: _name(name), _expression(expression), _sentence(sentence) {
}
ExecuteResult SentenceForeach::Execute(std::shared_ptr<Space> space) {
	if (!_expression || !_sentence) {
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_expression->Execute(space))) {
		return ExecuteResult::Failed;
	}
	if (!ValueTool::IsArray(_expression->GetValue())) {
		return ExecuteResult::Failed;
	}
	auto& arr = std::static_pointer_cast<ValueArray>(_expression->GetValue())->GetArray();
	if (arr.empty()) {
		return ExecuteResult::Successed;
	}

	auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Loop, space));
	auto itemVariable = std::shared_ptr<Variable>(new Variable(_name, VariableAttribute::None));
	if (!tempSpace->AddVariable(itemVariable)) {
		return ExecuteResult::Failed;
	}
	for (auto item : arr) {
		itemVariable->SetValue(item);
		auto contentSpace = std::shared_ptr<Space>(new Space(SpaceType::Loop, tempSpace));
		auto ret = _sentence->Execute(contentSpace);
		if (!IsSuccess(ret)) {
			return ExecuteResult::Failed;
		}
		if (ret == ExecuteResult::Break) {
			break;
		}
		if (ret == ExecuteResult::Return) {
			SetReturnValue(std::static_pointer_cast<SentenceReturn>(_sentence)->GetReturnValue());
			return ExecuteResult::Return;
		}
	}

	return ExecuteResult::Successed;
}