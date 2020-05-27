#include "SentenceExpressionNew.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceExpressionNew::SentenceExpressionNew(const std::string& name)
	: _name(name) {
}

ExecuteResult SentenceExpressionNew::Execute(std::shared_ptr<Space> space) {
	auto variable = space->FindVariable(_name);
	if (!variable) {
		ErrorLogger::LogRuntimeError(_name);
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::New, "The \"" + _name + "\" not found!");
		return ExecuteResult::Failed;
	}
	auto newValue = variable->GetValue()->Clone();
	SetValue(newValue);
	return ExecuteResult::Successed;
}
