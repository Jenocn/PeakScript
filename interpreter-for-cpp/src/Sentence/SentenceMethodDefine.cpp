#include "SentenceMethodDefine.h"
#include "../Method.h"

using namespace peak::interpreter;

SentenceMethodDefine::SentenceMethodDefine(const std::string& name)
	: _name(name) {
}

void SentenceMethodDefine::PushParam(const std::string& name) {
	_parameters.emplace_back(name);
}
void SentenceMethodDefine::SetSentence(std::shared_ptr<Sentence> sentence) {
	_sentence = sentence;
}

bool SentenceMethodDefine::Execute(std::shared_ptr<Space> space) {
	if (_name.empty()) {
		return false;
	}
	auto method = std::shared_ptr<Method>(new Method(_name));
	method->SetSentenceBody(_sentence);
	method->SetParameters(_parameters);
	if (!space->AddMethod(method)) {
		return false;
	}
	return true;
}
