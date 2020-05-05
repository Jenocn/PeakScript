#include "SentenceLoop.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceLoop::SentenceLoop(const std::string& indexParam, std::shared_ptr<SentenceExpression> condition, std::shared_ptr<Sentence> sentence)
	: _indexParam(indexParam), _condition(condition), _sentence(sentence) {
}
ExecuteResult SentenceLoop::Execute(std::shared_ptr<Space> space) {
	if (!_condition) {
		return ExecuteResult::Failed;
	}
	if (!_sentence) {
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_condition->Execute(space))) {
		return ExecuteResult::Failed;
	}
	auto value = _condition->GetValue();
	if (!ValueTool::IsNumber(value)) {
		return ExecuteResult::Failed;
	}
	auto count = std::max(0, static_cast<int>(std::static_pointer_cast<ValueNumber>(value)->GetValue()));
	auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Loop, space));
	if (_indexParam.empty()) {
		for (int i = 0; i < count; ++i) {
			auto ret = _sentence->Execute(tempSpace);
			if (!IsSuccess(ret)) {
				return ExecuteResult::Failed;
			}
			if (ret == ExecuteResult::Break) {
				break;
			}
		}
	} else {
		auto indexVariable = std::shared_ptr<Variable>(new Variable(_indexParam, VariableAttribute::None));
		if (!tempSpace->AddVariable(indexVariable)) {
			return ExecuteResult::Failed;
		}
		for (int i = 0; i < count; ++i) {
			if (!indexVariable->SetValue(std::shared_ptr<ValueNumber>(new ValueNumber(i)))) {
				return ExecuteResult::Failed;
			}
			auto ret = _sentence->Execute(tempSpace);
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
	}
	return ExecuteResult::Successed;
}