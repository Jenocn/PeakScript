#include "SentenceWhile.h"
#include "../Value/ValueTool.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceWhile::SentenceWhile(std::shared_ptr<SentenceExpression> expression, std::shared_ptr<Sentence> sentence)
	: _expression(expression), _sentence(sentence) {
}
ExecuteResult SentenceWhile::Execute(std::shared_ptr<Space> space) {
	if (!_expression) {
		return ExecuteResult::Failed;
	}
	if (_sentence) {
		auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Loop, space));
		while (true) {
			if (!IsSuccess(_expression->Execute(space))) {
				return ExecuteResult::Failed;
			}
			if (!ValueTool::ToLogic(_expression->GetValue())) {
				break;
			}
			tempSpace->Clear();
			auto ret = _sentence->Execute(tempSpace);
			if (!IsSuccess(ret)) {
				return ExecuteResult::Failed;
			}
			if (ret == ExecuteResult::Break) {
				break;
			}
			if (ret == ExecuteResult::Return) {
				SetReturnValue(std::static_pointer_cast<SentenceReturn>(_sentence)->GetReturnValue());
				return ExecuteResult::Return;
			}
		}
	} else {
		while (true) {
			if (!IsSuccess(_expression->Execute(space))) {
				return ExecuteResult::Failed;
			}
			if (!ValueTool::ToLogic(_expression->GetValue())) {
				break;
			}
		}
	}
	return ExecuteResult::Successed;
}