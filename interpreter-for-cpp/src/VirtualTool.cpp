#include "VirtualTool.h"
#include "Runtime/System.h"

using namespace peak;
using namespace peak::interpreter;

std::string VirtualTool::OpenSrc(const std::string& filename) {
	return System::OpenSrc(filename);
}
