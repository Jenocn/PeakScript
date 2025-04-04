#include "sentence_export.h"
#include "runtime/module.h"
#include "runtime/module_pool.h"

using namespace peak;

SentenceExport::SentenceExport(const std::string& moduleName)
	: _moduleName(moduleName) {
}

ExecuteResult SentenceExport::Execute(std::shared_ptr<Space> space) {
	if (space->GetSpaceType() != SpaceType::None) {
		ErrorLogger::LogRuntimeError(_moduleName);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Export, "The module \"" + _moduleName + "\" can't export here!");
		return ExecuteResult::Failed;
	}
	if (!space->SetExportModule(_moduleName)) {
		ErrorLogger::LogRuntimeError(_moduleName);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Export, "The module \"" + _moduleName + "\" already export!");
		return ExecuteResult::Failed;
	}
	auto module = std::shared_ptr<Module>(new Module(_moduleName, space));
	if (!ModulePool::GetInstance()->AddModule(_moduleName, module)) {
		ErrorLogger::LogRuntimeError(_moduleName);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Export, "The module \"" + _moduleName + "\" already exists!");
		return ExecuteResult::Failed;
	}
	return ExecuteResult::Successed;
}