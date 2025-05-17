#include <iostream>
#include <peak.h>

int main(int argc, char** argv) {
	peak::System::AddSearchDir(std::filesystem::current_path().string());
	peak::System::AddSearchDir(std::filesystem::path(argv[0]).parent_path().string());

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