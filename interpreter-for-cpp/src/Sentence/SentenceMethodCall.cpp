#include "SentenceMethodCall.h"
#include "../Method.h"

using namespace peak::interpreter;

SentenceMethodCall::SentenceMethodCall(const std::string& name)
	: _name(name) {
}

bool SentenceMethodCall::Execute(std::shared_ptr<Space> space) {
	auto method = space->FindMethod(_name);
	if (!method) {
		return false;
	}
	std::vector<std::shared_ptr<Value>> tempArgs;
	for (auto arg : _args) {
		if (!arg->Execute(space)) {
			return false;
		}
		tempArgs.emplace_back(arg->GetValue());
	}
	auto resultValue = method->Execute(space, tempArgs);
	if (!resultValue) {
		return false;
	}
	SetValue(resultValue);
	return true;
}