#include "SentenceFunctionDefine.h"
#include "../Sentence/SentenceReturn.h"
#include "../Value/ValueFunction.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceFunctionDefine::SentenceFunctionDefine(const std::string& name, const std::vector<std::string>& params, std::shared_ptr<Sentence> content)
	: _name(name), _params(params), _content(content) {
}
ExecuteResult SentenceFunctionDefine::Execute(std::shared_ptr<Space> space) {
	auto func = [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> space) -> std::shared_ptr<Value> {
		auto result = _content->Execute(space);
		if (!IsSuccess(result)) {
			return nullptr;
		}
		if (result == ExecuteResult::Return) {
			return std::static_pointer_cast<SentenceReturn>(_content)->GetReturnValue();
		}
		return std::shared_ptr<Value>(new ValueNull());
	};

	auto variable = space->FindVariableFromTop(_name);
	if (variable) {
		auto value = variable->GetValue();
		if (ValueTool::IsFunction(value)) {
			if (std::static_pointer_cast<ValueFunction>(value)->AddFunction(_params, func)) {
				return ExecuteResult::Successed;
			}
		}
		ErrorLogger::LogRuntimeError(_name);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::FunctionDefine, "The \"" + _name + "\" is exist!");
		return ExecuteResult::Failed;
	} else {
		variable = std::shared_ptr<Variable>(new Variable(_name, VariableAttribute::None));
		auto value = std::shared_ptr<ValueFunction>(new ValueFunction(_params, func));
		variable->SetValue(value);
		space->AddVariable(variable);
	}

	return ExecuteResult::Successed;
}