#include "SentenceFunctionDefine.h"
#include "../Value/ValueFunction.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceFunctionDefine::SentenceFunctionDefine(const std::string& name)
	: _name(name) {
}

void SentenceFunctionDefine::PushParam(const std::string& name) {
	_parameters.emplace_back(name);
}
void SentenceFunctionDefine::SetSentence(std::shared_ptr<Sentence> sentence) {
	_sentence = sentence;
}

ExecuteResult SentenceFunctionDefine::Execute(std::shared_ptr<Space> space) {
	if (_name.empty()) {
		return ExecuteResult::Failed;
	}
	auto func = std::shared_ptr<ValueFunction>(new ValueFunction(_name));
	func->SetSentenceBody(_sentence);
	func->SetParameters(_parameters);
	auto variable = std::shared_ptr<Variable>(new Variable(_name));
	variable->SetValue(func);
	if (!space->AddVariable(variable)) {
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}
