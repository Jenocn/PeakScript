#pragma once

#include "Sentence.h"

namespace peak::interpreter {

class SentenceExpression;

class SentenceReturn : public Sentence {
public:
	SentenceReturn();
	SentenceReturn(std::shared_ptr<SentenceExpression> expression);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

	std::shared_ptr<Value> GetReturnValue() const;

protected:
	void SetReturnValue(std::shared_ptr<Value> value);

private:
	std::shared_ptr<SentenceExpression> _expression{nullptr};
	std::shared_ptr<Value> _returnValue{nullptr};
};
} // namespace peak::interpreter