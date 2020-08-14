
#include "../../interpreter-for-cpp/src/peak.h"

using namespace peak;

int main(int argc, char** argv) {
	for (int i = 1; i < argc; ++i) {
		auto journey = VirtualMachine::LoadFile(argv[i]);
		if (journey) {
			journey->Execute();
		}
	}
	return 0;
}