#include "sentence_expression_new.h"
#include "runtime/value/value_tool.h"
#include "runtime/variable.h"

using namespace peak;

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
