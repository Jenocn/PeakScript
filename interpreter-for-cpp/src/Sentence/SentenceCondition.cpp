#include "SentenceCondition.h"
#include "SentenceExpression.h"
#include "../Value/ValueTool.h"

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

bool SentenceCondition::Execute(std::shared_ptr<Space> space) {
	if (!_expression) {
		return false;
	}
	if (!_expression->Execute(space)) {
		return false;
	}
	if (ValueTool::ToLogic(_expression->GetValue())) {
		if (_sentenceTrue) {
			auto tempSpace = std::shared_ptr<Space>(new Space(space));
			if (!_sentenceTrue->Execute(tempSpace)) {
				return false;
			}
		}
	} else {
		if (_sentenceFalse) {
			auto tempSpace = std::shared_ptr<Space>(new Space(space));
			if (!_sentenceFalse->Execute(tempSpace)) {
				return false;
			}
		}
	}
	return true;
}
