#include "virtual_tool.h"
#include "runtime/system.h"

using namespace peak;
using namespace peak;

std::string VirtualTool::OpenSrc(const std::string& filename) {
	return System::OpenSrc(filename);
}
