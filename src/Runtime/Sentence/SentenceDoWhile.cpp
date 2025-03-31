#include "SentenceDoWhile.h"
#include "../Value/ValueTool.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceDoWhile::SentenceDoWhile(std::shared_ptr<SentenceExpression> expression, std::shared_ptr<Sentence> sentence)
	: _expression(expression), _sentence(sentence) {
}
ExecuteResult SentenceDoWhile::Execute(std::shared_ptr<Space> space) {
	auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Loop, space));
	while (true) {
		tempSpace->Clear();
		auto ret = _sentence->Execute(tempSpace);

		if (!IsSuccess(ret)) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::DoWhile, "The sentence execute failed!");
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

		if (!IsSuccess(_expression->Execute(space))) {
			ErrorLogger::LogRuntimeError(ErrorRuntimeCode::DoWhile, "The condition expression execute failed!");
			return ExecuteResult::Failed;
		}
		if (!ValueTool::ToLogic(_expression->GetValue())) {
			break;
		}
	}
	tempSpace->Clear();
	return ExecuteResult::Successed;
}