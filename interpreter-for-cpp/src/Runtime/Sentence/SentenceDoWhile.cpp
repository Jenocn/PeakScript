#include "SentenceDoWhile.h"
#include "../Value/ValueTool.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceDoWhile::SentenceDoWhile(std::shared_ptr<SentenceExpression> expression, std::shared_ptr<Sentence> sentence)
	: _expression(expression), _sentence(sentence) {
}
ExecuteResult SentenceDoWhile::Execute(std::shared_ptr<Space> space) {
	if (!_sentence || !_expression) {
		return ExecuteResult::Failed;
	}
	auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Loop, space));
	while (true) {
		tempSpace->Clear();
		if (!IsSuccess(_sentence->Execute(tempSpace))) {
			return ExecuteResult::Failed;
		}
		if (!IsSuccess(_expression->Execute(space))) {
			return ExecuteResult::Failed;
		}
		if (!ValueTool::ToLogic(_expression->GetValue())) {
			break;
		}
	}
	return ExecuteResult::Successed;
}