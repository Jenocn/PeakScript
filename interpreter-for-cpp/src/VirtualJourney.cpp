#include "VirtualJourney.h"

using namespace peak;
using namespace peak::interpreter;

VirtualJourney::VirtualJourney() {
	_space = std::shared_ptr<Space>(new Space(SpaceType::None));
}
VirtualJourney::VirtualJourney(std::shared_ptr<Space> parent) {
	_space = std::shared_ptr<Space>(new Space(SpaceType::None, parent));
}
bool VirtualJourney::Execute() {
	return true;
}
