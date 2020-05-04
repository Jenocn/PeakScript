#include "SentenceFunctionDefine.h"
#include "../Sentence/SentenceReturn.h"
#include "../Value/ValueFunction.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceFunctionDefine::SentenceFunctionDefine(const std::string& name, const std::vector<std::string>& params, std::shared_ptr<Sentence> content)
	: _params(params), _content(content) {
	_variable = std::shared_ptr<Variable>(new Variable(name));
}
ExecuteResult SentenceFunctionDefine::Execute(std::shared_ptr<Space> space) {
	if (!_content) {
		return ExecuteResult::Failed;
	}
	if (!space->AddVariable(_variable)) {
		return ExecuteResult::Failed;
	}
	_variable->SetValue(std::shared_ptr<ValueFunction>(new ValueFunction(_params, [this](std::shared_ptr<Space> space) -> std::shared_ptr<Value> {
		auto result = _content->Execute(space);
		if (!IsSuccess(result)) {
			return nullptr;
		}
		if (result == ExecuteResult::Return) {
			return std::static_pointer_cast<SentenceReturn>(_content)->GetReturnValue();
		}
		return std::shared_ptr<Value>(new ValueNull());
	})));
	return ExecuteResult::Successed;
}