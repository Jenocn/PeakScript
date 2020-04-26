#pragma once

#include "Value.h"
#include "ValueBool.h"
#include "ValueNull.h"
#include "ValueNumber.h"
#include "ValueString.h"
#include <memory>

namespace peak::interpreter {
class Value;

class ValueTool {
public:
	static bool IsNull(std::shared_ptr<Value> value);
	static bool IsBool(std::shared_ptr<Value> value);
	static bool IsNumber(std::shared_ptr<Value> value);
	static bool IsString(std::shared_ptr<Value> value);
	static std::string ToString(std::shared_ptr<Value> value);
};
} // namespace peak::interpreter