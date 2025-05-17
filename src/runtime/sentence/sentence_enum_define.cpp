#include "sentence_enum_define.h"
#include "runtime/value/value_tool.h"
#include "runtime/variable.h"

using namespace peak;

SentenceEnumDefine::SentenceEnumDefine(const std::string& name, const std::list<std::pair<std::string, std::shared_ptr<ValueNumber>>>& valueList)
	: _name(name), _valueList(valueList) {
}

ExecuteResult SentenceEnumDefine::Execute(std::shared_ptr<Space> space) {
	auto valueObject = std::make_shared<ValueObject>();
	auto variable = std::make_shared<Variable>(_name, VariableAttribute::Const, valueObject);
	if (!space->AddVariable(variable)) {
		ErrorLogger::LogRuntimeError(_name);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::EnumDefine, "The enum name \"" + _name + "\" is exist!");
		return ExecuteResult::Failed;
	}
	auto valueSpace = valueObject->GetSpace();
	for (auto& pair : _valueList) {
		auto valueVariable = std::make_shared<Variable>(pair.first, VariableAttribute::Const, pair.second);
		if (!valueSpace->AddVariable(valueVariable)) {
			ErrorLogger::LogRuntimeError(pair.first);
			ErrorLogger::LogRuntimeError(_name);
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::EnumDefine, "The item name \"" + _name + "\" is exist!");
			return ExecuteResult::Failed;
		}
	}
	return ExecuteResult::Successed;
}
