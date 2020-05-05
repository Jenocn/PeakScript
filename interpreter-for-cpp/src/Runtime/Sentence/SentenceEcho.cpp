#include "SentenceEcho.h"
#include "../Value/ValueTool.h"
#include "SentenceExpression.h"
#include "../System.h"

using namespace peak::interpreter;

SentenceEcho::SentenceEcho(std::shared_ptr<SentenceExpression> expression)
	: _expression(expression) {
}

ExecuteResult SentenceEcho::Execute(std::shared_ptr<Space> space) {
	if (!_expression || !IsSuccess(_expression->Execute(space))) {
		return ExecuteResult::Failed;
	}
	auto value = _expression->GetValue();
	System::Echo(ValueTool::ToString(value));
	
	return ExecuteResult::Successed;
}