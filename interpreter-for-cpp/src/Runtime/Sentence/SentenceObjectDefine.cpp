#include "SentenceObjectDefine.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceObjectDefine::SentenceObjectDefine(const std::string& name, std::list<std::shared_ptr<Sentence>>& sentenceList)
	: _name(name), _sentenceList(sentenceList) {
}

ExecuteResult SentenceObjectDefine::Execute(std::shared_ptr<Space> space) {

	auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Object));
	tempSpace->AddSpaceOfUsing(space);
	auto valueObject = std::shared_ptr<ValueObject>(new ValueObject(tempSpace));
	for (auto sentence : _sentenceList) {
		if (!IsSuccess(sentence->Execute(tempSpace))) {
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
