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
		while (true) {
			if (!IsSuccess(_expression->Execute(space))) {
				return ExecuteResult::Failed;
			}
			if (!ValueTool::ToLogic(_expression->GetValue())) {
				break;
			}
			auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Loop, space));
			if (!IsSuccess(_sentence->Execute(tempSpace))) {
				return ExecuteResult::Failed;
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