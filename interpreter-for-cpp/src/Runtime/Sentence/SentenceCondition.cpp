#include "SentenceCondition.h"
#include "../Value/ValueTool.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceCondition::SentenceCondition(std::shared_ptr<SentenceExpression> expression, std::shared_ptr<Sentence> sentenceTrue, std::shared_ptr<Sentence> sentenceFalse)
	: _expression(expression), _sentenceTrue(sentenceTrue), _sentenceFalse(sentenceFalse) {
}

ExecuteResult SentenceCondition::Execute(std::shared_ptr<Space> space) {
	if (!_expression) {
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_expression->Execute(space))) {
		return ExecuteResult::Failed;
	}
	bool bTrue = ValueTool::ToLogic(_expression->GetValue());
	auto tempSentence = bTrue ? _sentenceTrue : _sentenceFalse;
	if (tempSentence) {
		auto tempSpace = std::shared_ptr<Space>(new Space(SpaceType::Condition, space));
		auto executeRet = tempSentence->Execute(tempSpace);
		if (!IsSuccess(executeRet)) {
			return ExecuteResult::Failed;
		}
		if (executeRet == ExecuteResult::Return) {
			SetReturnValue(std::static_pointer_cast<SentenceReturn>(tempSentence)->GetReturnValue());
			return ExecuteResult::Return;
		}
	}

	return ExecuteResult::Successed;
}
