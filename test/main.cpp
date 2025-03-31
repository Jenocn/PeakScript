#include <iostream>
#include <VirtualMachine.h>
#include <VirtualJourney.h>
#include <VirtualTool.h>

int main(int argc, char** argv) {
	std::shared_ptr<peak::VirtualJourney> script { nullptr };
	if (argc > 1) {
		script = peak::VirtualMachine::LoadFile(argv[1]);
	} else {
		script = peak::VirtualMachine::LoadFile("./main.peak");
	}
	if (script) {
		script->Execute();
	}

	getchar();

	return 0;
}