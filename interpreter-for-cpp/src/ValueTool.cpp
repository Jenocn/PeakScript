#include "ValueTool.h"

using namespace peak::interpreter;

bool ValueTool::IsNull(std::shared_ptr<Value> value) {
	return !value || (value->GetType() == ValueNull::Type());
}
bool ValueTool::IsBool(std::shared_ptr<Value> value) {
	return value && (value->GetType() == ValueBool::Type());
}
bool ValueTool::IsNumber(std::shared_ptr<Value> value) {
	return value && (value->GetType() == ValueNumber::Type());
}
bool ValueTool::IsString(std::shared_ptr<Value> value) {
	return value && (value->GetType() == ValueString::Type());
}
std::string ValueTool::ToString(std::shared_ptr<Value> value) {
	if (IsNull(value)) {
		return "null";
	}
	if (IsBool(value)) {
		return std::static_pointer_cast<ValueBool>(value)->GetValue() ? "true" : "false";
	}
	if (IsNumber(value)) {
		char ch[24];
		sprintf(ch, "%0.15lg", std::static_pointer_cast<ValueNumber>(value)->GetValue());
		return ch;
	}
	if (IsString(value)) {
		return std::static_pointer_cast<ValueString>(value)->GetValue();
	}
	return "";
}
