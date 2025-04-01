
#include "virtual_machine.h"
#include "base/error_logger.h"
#include "runtime/executer.h"
#include "runtime/module_pool.h"
#include "runtime/system.h"
#include "virtual_journey.h"
#include "virtual_tool.h"

using namespace peak;
using namespace peak;

std::shared_ptr<VirtualJourney> VirtualMachine::Load(const std::string& src) {
	auto executer = Executer::Create(src);
	if (executer) {
		return std::shared_ptr<VirtualJourney>(new VirtualJourney(executer));
	}
	return nullptr;
}

std::shared_ptr<VirtualJourney> VirtualMachine::LoadFile(const std::string& filename) {
	const auto& src = VirtualTool::OpenSrc(filename);
	return Load(src);
}

void VirtualMachine::LocateLogger(std::function<void(const std::string&)> logger) {
	LocateLogger(logger, logger);
}
void VirtualMachine::LocateLogger(std::function<void(const std::string&)> echo, std::function<void(const std::string&)> errorLogger) {
	System::LocateEcho(echo);
	ErrorLogger::Locate(errorLogger);
}

void VirtualMachine::LocateOpenSrc(std::function<std::string(const std::string&)> func) {
	System::LocateOpenSrc(func);
}

ModulePool* VirtualMachine::GetModulePool() {
	return ModulePool::GetInstance();
}
