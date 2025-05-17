#include "sentence_while.h"
#include "runtime/value/value_tool.h"
#include "sentence_expression.h"

using namespace peak;

SentenceWhile::SentenceWhile(std::shared_ptr<SentenceExpression> expression, std::shared_ptr<Sentence> sentence)
	: _expression(expression), _sentence(sentence) {
}
ExecuteResult SentenceWhile::Execute(std::shared_ptr<Space> space) {
	if (_sentence) {
		auto tempSpace = std::make_shared<Space>(SpaceType::Loop, space);
		while (true) {
			if (!IsSuccess(_expression->Execute(space))) {
				ErrorLogger::LogRuntimeError(ErrorRuntimeCode::While, "The condition expression execute failed!");
				return ExecuteResult::Failed;
			}
			if (!ValueTool::ToLogic(_expression->GetValue().get())) {
				break;
			}
			tempSpace->Clear();
			auto ret = _sentence->Execute(tempSpace);
			if (!IsSuccess(ret)) {
				ErrorLogger::LogRuntimeError(ErrorRuntimeCode::While, "The sentence execute failed!");
				return ExecuteResult::Failed;
			}
			if (ret == ExecuteResult::Break) {
				break;
			}
			if (ret == ExecuteResult::Return) {
				SetReturnValue(std::static_pointer_cast<SentenceReturn>(_sentence)->GetReturnValue());
				tempSpace->Clear();
				return ExecuteResult::Return;
			}
		}
		tempSpace->Clear();

	} else {
		while (true) {
			if (!IsSuccess(_expression->Execute(space))) {
				ErrorLogger::LogRuntimeError(ErrorRuntimeCode::While, "The expression execute failed!");
				return ExecuteResult::Failed;
			}
			if (!ValueTool::ToLogic(_expression->GetValue().get())) {
				break;
			}
		}
	}
	return ExecuteResult::Successed;
}