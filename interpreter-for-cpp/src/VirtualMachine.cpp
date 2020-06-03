
#include "VirtualMachine.h"
#include "Base/ErrorLogger.h"
#include "Runtime/Executer.h"
#include "Runtime/ModulePool.h"
#include "Runtime/System.h"
#include "VirtualTool.h"

using namespace peak;
using namespace peak::interpreter;

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
