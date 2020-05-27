/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "Value.h"
#include "ValueArray.h"
#include "ValueBool.h"
#include "ValueFunction.h"
#include "ValueNull.h"
#include "ValueNumber.h"
#include "ValueObject.h"
#include "ValueString.h"

namespace peak {
namespace interpreter {
class Value;

class ValueTool {
public:
	static bool IsNull(std::shared_ptr<Value> value);
	static bool IsBool(std::shared_ptr<Value> value);
	static bool IsNumber(std::shared_ptr<Value> value);
	static bool IsString(std::shared_ptr<Value> value);
	static bool IsFunction(std::shared_ptr<Value> value);
	static bool IsArray(std::shared_ptr<Value> value);
	static bool IsObject(std::shared_ptr<Value> value);
	static std::string ToString(std::shared_ptr<Value> value);
	static std::string ToTypeString(std::shared_ptr<Value> value);
	static bool ToLogic(std::shared_ptr<Value> value);
	static bool Equal(std::shared_ptr<Value> a, std::shared_ptr<Value> b);
	static bool More(std::shared_ptr<Value> a, std::shared_ptr<Value> b);

	static bool IsInteger(std::shared_ptr<Value> value);
};
} // namespace interpreter
} // namespace peak