#pragma once

#include "Value.h"

namespace peak::interpreter {
class ValueBool : public TypeValue<ValueBool> {
public:
	ValueBool(bool value);
	bool GetValue() const;
private:
	bool _value{false};
};
} // namespace peak::interpreter