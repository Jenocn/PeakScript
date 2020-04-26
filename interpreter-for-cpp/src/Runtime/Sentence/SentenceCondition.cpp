#include "SentenceCondition.h"
#include "../Value/ValueTool.h"
#include "SentenceExpression.h"

using namespace peak::interpreter;

SentenceCondition::SentenceCondition(std::shared_ptr<SentenceExpression> expression)
	: _expression(expression) {
}
void SentenceCondition::SetSentenceWhenTrue(std::shared_ptr<Sentence> sentence) {
	_sentenceTrue = sentence;
}
void SentenceCondition::SetSentenceWhenFalse(std::shared_ptr<Sentence> sentence) {
	_sentenceFalse = sentence;
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
