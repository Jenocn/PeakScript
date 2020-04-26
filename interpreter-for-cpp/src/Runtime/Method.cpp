#include "Method.h"
#include "Sentence/Sentence.h"
#include "Sentence/SentenceBlock.h"
#include "Value/ValueTool.h"
#include "Variable.h"

using namespace peak::interpreter;

Method::Method(const std::string& name)
	: _name(name) {
}

const std::string& Method::GetName() const {
	return _name;
}

void Method::SetSentenceBody(std::shared_ptr<Sentence> sentence) {
	_sentence = sentence;
}
void Method::SetParameters(const std::vector<std::string>& args) {
	_parameters = args;
}

std::shared_ptr<Value> Method::Execute(std::shared_ptr<Space> space) {
	auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Method, space));

	auto size = _parameters.size();
	if (size > _args.size()) {
		return nullptr;
	}
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
		if (!Sentence::IsSuccess(_sentence->Execute(tempSpace))) {
			return nullptr;
		}
	}

	// temp todo... // return support

	return std::shared_ptr<Value>(new ValueNull());
}

std::shared_ptr<Value> Method::Execute(std::shared_ptr<Space> space, const std::vector<std::shared_ptr<Value>>& args) {
	_args = args;
	return Execute(space);
}

void Method::_PushParameter(const std::string& arg) {
	_parameters.emplace_back(arg);
}

void Method::_PushArg(std::shared_ptr<Value> arg) {
	_args.emplace_back(arg);
}
