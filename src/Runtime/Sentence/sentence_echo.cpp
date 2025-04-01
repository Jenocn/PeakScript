#include "sentence_echo.h"
#include "runtime/system.h"
#include "runtime/value/value_tool.h"
#include "sentence_expression.h"

using namespace peak;

SentenceEcho::SentenceEcho(std::shared_ptr<SentenceExpression> expression)
	: _expression(expression) {
}

ExecuteResult SentenceEcho::Execute(std::shared_ptr<Space> space) {
	if (!IsSuccess(_expression->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Echo, "The parameter expression execute failed!");
		return ExecuteResult::Failed;
	}
	auto value = _expression->GetValue();
	System::Echo(ValueTool::ToString(value));

	return ExecuteResult::Successed;
}