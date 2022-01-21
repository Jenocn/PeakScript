#include "SentenceExpressionInside.h"
#include "../Value/ValueTool.h"
#include "SentenceExpressionVariable.h"

using namespace peak::interpreter;

SentenceExpressionInside::SentenceExpressionInside(std::shared_ptr<SentenceExpression> header, std::vector<std::shared_ptr<SentenceExpression>> insides)
	: _header(header), _insides(insides) {
}
ExecuteResult SentenceExpressionInside::Execute(std::shared_ptr<Space> space) {
	if (!Sentence::IsSuccess(_header->Execute(space))) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Inside, "The header expression execute failed!");
		return ExecuteResult::Failed;
	}
	auto headerValue = _header->GetValue();
	if (!ValueTool::IsObject(headerValue)) {
		ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Inside, "The header expression isn't a object!");
		return ExecuteResult::Failed;
	}
	auto tempValue = headerValue;
	for (auto expression : _insides) {
		if (!ValueTool::IsObject(tempValue)) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Inside, "The expression isn't a object!");
			return ExecuteResult::Failed;
		}
		auto objSpace = std::static_pointer_cast<ValueObject>(tempValue)->GetSpace();
		auto expType = expression->GetExpressionType();
		auto executeRet = ExecuteResult::Failed;
		if (expType == ExpressionType::Function) {
			executeRet = std::static_pointer_cast<SentenceExpressionFunctionCall>(expression)->ExecuteFromInside(objSpace, space);
		} else {
			executeRet = expression->Execute(objSpace);
		}
		if (!Sentence::IsSuccess(executeRet)) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::Inside, "The inside expression execute failed!");
			return ExecuteResult::Failed;
		}
		tempValue = expression->GetValue();
	}
	SetValue(tempValue);
	return ExecuteResult::Successed;
}