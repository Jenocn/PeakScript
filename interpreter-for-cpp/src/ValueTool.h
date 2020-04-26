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
	static bool ToLogic(std::shared_ptr<Value> value);
	static bool Equal(std::shared_ptr<Value> a, std::shared_ptr<Value> b);
	static bool More(std::shared_ptr<Value> a, std::shared_ptr<Value> b);
};
} // namespace peak::interpreter