
#include "virtual_machine.h"
#include "base/error_logger.h"
#include "runtime/executer.h"
#include "runtime/module_pool.h"
#include "runtime/system.h"
#include "virtual_journey.h"

using namespace peak;

std::shared_ptr<VirtualJourney> VirtualMachine::Load(const std::string& src) {
	auto executer = Executer::Create(src);
	if (executer) {
		return std::make_shared<VirtualJourney>(executer);
	}
	return nullptr;
}

std::shared_ptr<VirtualJourney> VirtualMachine::LoadFile(const std::string& filename) {
	std::string absPath;
	return Load(System::OpenSrc(filename, absPath));
}

void VirtualMachine::LocateLogger(std::function<void(const std::string&)> logger) {
	LocateLogger(logger, logger);
}
void VirtualMachine::LocateLogger(std::function<void(const std::string&)> echo, std::function<void(const std::string&)> errorLogger) {
	System::LocateEcho(echo);
	ErrorLogger::Locate(errorLogger);
}

void VirtualMachine::LocateLoadText(std::function<std::string(const std::string&)> func) {
	System::LocateLoadText(func);
}

ModulePool* VirtualMachine::GetModulePool() {
	return ModulePool::GetInstance();
}
