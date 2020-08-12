
#include <peak.h>

#pragma comment(lib, "libpeak")

using namespace peak;

int main(int argc, char** argv) {
	for (int i = 1; i < argc; ++i) {
		auto journey = VirtualMachine::LoadFile(argv[i]);
		if (journey) {
			journey->Execute();
		}
	}
	getchar();
	return 0;
}