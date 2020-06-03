#include "SentenceImport.h"
#include "../Module.h"
#include "../ModulePool.h"

using namespace peak::interpreter;

SentenceImport::SentenceImport(const std::string& moduleName)
	: _moduleName(moduleName) {
}
ExecuteResult SentenceImport::Execute(std::shared_ptr<Space> space) {
	auto module = ModulePool::GetInstance()->UseModule(_moduleName);
	if (!module) {
		ErrorLogger::LogRuntimeError(_moduleName);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Import, "The module \"" + _moduleName + "\" import failed!");
		return ExecuteResult::Failed;
	}
	if (!space->UseModule(module)) {
		ErrorLogger::LogRuntimeError(_moduleName);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Import, "The module \"" + _moduleName + "\" import failed!");
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}