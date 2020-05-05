
#include "VirtualMachine.h"
#include "Grammar/ParseTool.h"

using namespace peak;
using namespace peak::interpreter;

std::shared_ptr<VirtualJourney> VirtualMachine::Load(const std::string& src, std::shared_ptr<Space> parent) {
	auto parseData = ParseTool::Load(src);
	if (!parseData->bSuccess) {
		return nullptr;
	}
	return std::shared_ptr<VirtualJourney>(new VirtualJourney(parseData->sentenceList, parent));
}
