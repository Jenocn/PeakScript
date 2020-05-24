#include "SentenceEcho.h"
#include "../System.h"
#include "../Value/ValueTool.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

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