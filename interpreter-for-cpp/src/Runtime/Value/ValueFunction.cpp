#include "ValueFunction.h"
#include "../Sentence/Sentence.h"
#include "../Sentence/SentenceReturn.h"
#include "../Variable.h"
#include "ValueTool.h"

using namespace peak::interpreter;

ValueFunction::ValueFunction(const std::string& name)
	: _name(name) {
}

const std::string& ValueFunction::GetName() const {
	return _name;
}

void ValueFunction::SetSentenceBody(std::shared_ptr<Sentence> sentence) {
	_sentence = sentence;
}
void ValueFunction::SetParameters(const std::vector<std::string>& args) {
	_parameters = args;
}

std::shared_ptr<Value> ValueFunction::Execute(std::shared_ptr<Space> space) {

	auto size = _parameters.size();
	if (size > _args.size()) {
		return nullptr;
	}
	auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::ValueFunction, space));
	for (std::size_t i = 0; i < size; ++i) {
		const auto& paramName = _parameters[i];
		auto paramValue = _args[i];
		auto paramVariable = std::shared_ptr<Variable>(new Variable(paramName));
		paramVariable->SetValue(_args[i]);
		if (!tempSpace->AddVariable(paramVariable)) {
			return nullptr;
		}
	}

	if (_sentence) {
		auto executeRet = _sentence->Execute(tempSpace);
		if (!Sentence::IsSuccess(executeRet)) {
			return nullptr;
		}
		if (executeRet == ExecuteResult::Return) {
			return std::static_pointer_cast<SentenceReturn>(_sentence)->GetReturnValue();
		}
	}
	return std::shared_ptr<Value>(new ValueNull());
}

std::shared_ptr<Value> ValueFunction::Execute(std::shared_ptr<Space> space, const std::vector<std::shared_ptr<Value>>& args) {
	_args = args;
	return Execute(space);
}

void ValueFunction::_PushParameter(const std::string& arg) {
	_parameters.emplace_back(arg);
}

void ValueFunction::_PushArg(std::shared_ptr<Value> arg) {
	_args.emplace_back(arg);
}
