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
	if (ValueTool::ToLogic(_expression->GetValue())) {
		if (_sentenceTrue) {
			auto tempSpace = std::shared_ptr<Space>(new Space(space));
			if (!IsSuccess(_sentenceTrue->Execute(tempSpace))) {
				return ExecuteResult::Failed;
			}
		}
	} else {
		if (_sentenceFalse) {
			auto tempSpace = std::shared_ptr<Space>(new Space(space));
			if (!IsSuccess(_sentenceFalse->Execute(tempSpace))) {
				return ExecuteResult::Failed;
			}
		}
	}
	return ExecuteResult::Successed;
}
