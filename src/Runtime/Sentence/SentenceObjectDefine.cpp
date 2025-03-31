#include "SentenceObjectDefine.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceObjectDefine::SentenceObjectDefine(const std::string& name, const std::string& parentName, std::list<std::shared_ptr<Sentence>>& sentenceList)
	: _name(name), _parentName(parentName), _sentenceList(sentenceList) {
}

ExecuteResult SentenceObjectDefine::Execute(std::shared_ptr<Space> space) {
	std::shared_ptr<ValueObject> parentObject{nullptr};
	if (!_parentName.empty()) {
		auto parentVariable = space->FindVariable(_parentName);
		if (!parentVariable) {
			ErrorLogger::LogRuntimeError(_parentName);
			ErrorLogger::LogRuntimeError(_name);
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ObjectDefine, "The extends object \"" + _parentName + "\" of \"" + _name + "\" not found!");
			return ExecuteResult::Failed;
		}
		auto parentValue = parentVariable->GetValue();
		if (!ValueTool::IsObject(parentValue)) {
			ErrorLogger::LogRuntimeError(_parentName);
			ErrorLogger::LogRuntimeError(_name);
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ObjectDefine, "The variable \"" + _parentName + "\" isn't a object!");
			return ExecuteResult::Failed;
		}
		parentObject = std::static_pointer_cast<ValueObject>(parentValue);
	}
	auto valueObject = std::shared_ptr<ValueObject>(new ValueObject(space, parentObject));
	auto objectSpace = valueObject->GetSpace();
	for (auto sentence : _sentenceList) {
		if (!IsSuccess(sentence->Execute(objectSpace))) {
			ErrorLogger::LogRuntimeError(_name);
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ObjectDefine, "The object build failed!");
			return ExecuteResult::Failed;
		}
	}

	if (!space->AddVariable(std::shared_ptr<Variable>(new Variable(_name, VariableAttribute::None, valueObject)))) {
		ErrorLogger::LogRuntimeError(_name);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::ObjectDefine, "The object \"" + _name + "\" is exist!");
		return ExecuteResult::Failed;
	}

	return ExecuteResult::Successed;
}
