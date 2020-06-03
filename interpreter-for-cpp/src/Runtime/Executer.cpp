#include "Executer.h"
#include "../Grammar/ParseTool.h"
#include "Sentence/Sentence.h"
#include "Space.h"

using namespace peak::interpreter;

std::shared_ptr<Executer> Executer::Create(const std::string& src) {
	if (src.empty()) {
		return nullptr;
	}
	auto parseData = ParseTool::Load(src);
	if (!parseData->bSuccess) {
		return nullptr;
	}
	return std::shared_ptr<Executer>(new Executer(parseData));
}

Executer::Executer(std::shared_ptr<ParseData> data)
	: _parseData(data) {
	_space = std::shared_ptr<Space>(new Space(SpaceType::None));
}

Executer::~Executer() {
	_space->Clear();
}

bool Executer::Execute() {
	_space->Clear();
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

std::shared_ptr<Variable> Executer::FindVariable(const std::string& name) {
	return _space->FindVariable(name);
}
bool Executer::AddVariable(std::shared_ptr<Variable> variable) {
	return _space->AddVariable(variable);
}
