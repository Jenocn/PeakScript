#pragma once

#include "Sentence.h"

namespace peak::interpreter {

class Value;

class SentenceExpression : public Sentence {
public:
	std::shared_ptr<Value> GetValue() const;

protected:
	void SetValue(std::shared_ptr<Value> value);

private:
	std::shared_ptr<Value> _value{nullptr};
};
} // namespace peak::interpreter