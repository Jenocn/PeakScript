#include "VirtualJourney.h"
#include "Runtime/Sentence/Sentence.h"

using namespace peak;
using namespace peak::interpreter;

VirtualJourney::VirtualJourney(const std::list<std::shared_ptr<interpreter::Sentence>>& sentenceList, std::shared_ptr<interpreter::Space> parent)
	: _sentenceList(sentenceList), _space(std::shared_ptr<Space>(new Space(SpaceType::None, parent))) {
}

bool VirtualJourney::Execute() {
	_space->Clear();
	for (auto sentence : _sentenceList) {
		if (!Sentence::IsSuccess(sentence->Execute(_space))) {
			return false;
		}
	}
	return true;
}

std::shared_ptr<Variable> VirtualJourney::FindVariable(const std::string& name) {
	return _space->FindVariable(name);
}
bool VirtualJourney::AddVariable(std::shared_ptr<Variable> variable) {
	return _space->AddVariable(variable);
}