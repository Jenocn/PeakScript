#include "SentenceExport.h"
#include "../Module.h"
#include "../ModulePool.h"

using namespace peak::interpreter;

SentenceExport::SentenceExport(const std::string& moduleName)
	: _moduleName(moduleName) {
}

ExecuteResult SentenceExport::Execute(std::shared_ptr<Space> space) {
	if (!space->SetExportModule(_moduleName)) {
		ErrorLogger::LogRuntimeError(_moduleName);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Export, "The module \"" + _moduleName + "\" export failed!");
		return ExecuteResult::Failed;
	}
	auto module = std::shared_ptr<Module>(new Module(_moduleName, space));
	if (!ModulePool::GetInstance()->AddModule(_moduleName, module, true)) {
		ErrorLogger::LogRuntimeError(_moduleName);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Export, "The module \"" + _moduleName + "\" export failed!");
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}