#include "executer.h"
#include "grammar/parse.h"
#include "sentence/sentence.h"
#include "space.h"

using namespace peak;

std::shared_ptr<Executer> Executer::Create(const std::string& src) {
	if (src.empty()) {
		return nullptr;
	}
	auto parseData = Parse::Load(src);
	if (!parseData->bSuccess) {
		return nullptr;
	}
	return std::make_shared<Executer>(parseData);
}

Executer::Executer(std::shared_ptr<ParseData> data)
	: _parseData(data) {
	_space = std::make_shared<Space>(SpaceType::None);
	_outsideSpace = std::make_shared<Space>(SpaceType::None);
}

Executer::~Executer() {
	_space->Clear();
	_outsideSpace->Clear();
}

bool Executer::Execute() {
	_space->Clear();
	_space->AddSpaceOfUsing(_outsideSpace);
	for (auto sentence : _parseData->sentenceList) {
		if (!Sentence::IsSuccess(sentence->Execute(_space))) {
			return false;
		}
	}
	return true;
}

std::shared_ptr<Space> Executer::GetSpace() const {
	return _space;
}

std::shared_ptr<Variable> Executer::FindVariable(const std::string& name) const {
	return _space->FindVariable(name);
}
bool Executer::AddVariable(std::shared_ptr<Variable> variable) {
	return _outsideSpace->AddVariable(variable);
}
