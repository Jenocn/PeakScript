
#include "../../interpreter-for-cpp/src/VirtualMachine.h"
#include "../../interpreter-for-cpp/src/VirtualTool.h"

using namespace peak;

int main(int argc, char** argv) {
	for (int i = 1; i < argc; ++i) {
		std::cout << argv[i] << std::endl;
		const auto& src = VirtualTool::OpenFile(argv[i]);
		if (src.empty()) {
			continue;
		}
		auto journey = VirtualMachine::Load(src);
		if (journey) {
			journey->Execute();
		}
	}
	return 0;
}