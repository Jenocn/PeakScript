#include "SentenceFunctionDefine.h"
#include "../Sentence/SentenceReturn.h"
#include "../Value/ValueFunction.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceFunctionDefine::SentenceFunctionDefine(const std::string& name, const std::vector<std::string>& params, std::shared_ptr<Sentence> content)
	: _params(params), _content(content) {
	_variable = std::shared_ptr<Variable>(new Variable(name, VariableAttribute::None));
}
ExecuteResult SentenceFunctionDefine::Execute(std::shared_ptr<Space> space) {
	if (!space->AddVariable(_variable)) {
		ErrorLogger::LogRuntimeError(_variable->GetName());
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::FunctionDefine, "The \"" + _variable->GetName() + "\" is exist!");
		return ExecuteResult::Failed;
	}
	auto func = std::shared_ptr<ValueFunction>(new ValueFunction(_params, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> space) -> std::shared_ptr<Value> {
		auto result = _content->Execute(space);
		if (!IsSuccess(result)) {
			return nullptr;
		}
		if (result == ExecuteResult::Return) {
			return std::static_pointer_cast<SentenceReturn>(_content)->GetReturnValue();
		}
		return std::shared_ptr<Value>(new ValueNull());
	}));
	_variable->SetValue(func);
	return ExecuteResult::Successed;
}