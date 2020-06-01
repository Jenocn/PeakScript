#include "SentenceEnumDefine.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceEnumDefine::SentenceEnumDefine(const std::string& name, const std::list<std::pair<std::string, std::shared_ptr<ValueNumber>>>& valueList)
	: _name(name), _valueList(valueList) {
}

ExecuteResult SentenceEnumDefine::Execute(std::shared_ptr<Space> space) {
	auto valueObject = std::shared_ptr<ValueObject>(new ValueObject());
	auto variable = std::shared_ptr<Variable>(new Variable(_name, VariableAttribute::Const, valueObject));
	if (!space->AddVariable(variable)) {
		ErrorLogger::LogRuntimeError(_name);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::EnumDefine, "The enum name \"" + _name + "\" is exist!");
		return ExecuteResult::Failed;
	}
	auto valueSpace = valueObject->GetSpace();
	for (auto& pair : _valueList) {
		auto valueVariable = std::shared_ptr<Variable>(new Variable(pair.first, VariableAttribute::Const, pair.second));
		if (!valueSpace->AddVariable(valueVariable)) {
			ErrorLogger::LogRuntimeError(pair.first);
			ErrorLogger::LogRuntimeError(_name);
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::EnumDefine, "The item name \"" + _name + "\" is exist!");
			return ExecuteResult::Failed;
		}
	}
	return ExecuteResult::Successed;
}
