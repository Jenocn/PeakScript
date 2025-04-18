#include "value_tool.h"

using namespace peak;

static const std::unordered_map<int, std::string> TypeStringMap = {
	{ValueNull::Type(), "null"},
	{ValueBool::Type(), "bool"},
	{ValueArray::Type(), "array"},
	{ValueString::Type(), "string"},
	{ValueNumber::Type(), "number"},
	{ValueFunction::Type(), "function"},
	{ValueObject::Type(), "object"},
};

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
bool ValueTool::IsFunction(std::shared_ptr<Value> value) {
	return value && (value->GetType() == ValueFunction::Type());
}
bool ValueTool::IsArray(std::shared_ptr<Value> value) {
	return value && (value->GetType() == ValueArray::Type());
}
bool ValueTool::IsObject(std::shared_ptr<Value> value) {
	return value && (value->GetType() == ValueObject::Type());
}

std::string ValueTool::ToString(std::shared_ptr<Value> value) {
	if (!value) {
		return ValueNull::DEFAULT_VALUE->ToString();
	}
	return value->ToString();
}

std::string ValueTool::ToTypeString(std::shared_ptr<Value> value) {
	if (!value) {
		return ToTypeString(ValueNull::DEFAULT_VALUE);
	}
	auto ite = TypeStringMap.find(value->GetType());
	if (ite != TypeStringMap.end()) {
		return ite->second;
	}
	return "";
}

bool ValueTool::ToLogic(std::shared_ptr<Value> value) {
	if (IsNull(value)) {
		return false;
	}
	if (IsNumber(value)) {
		return std::static_pointer_cast<ValueNumber>(value)->GetValue() != 0;
	}
	if (IsBool(value)) {
		return std::static_pointer_cast<ValueBool>(value)->GetValue();
	}
	return true;
}

bool ValueTool::Equal(std::shared_ptr<Value> a, std::shared_ptr<Value> b) {
	if (a->GetType() != b->GetType()) {
		return false;
	}
	if (IsBool(a)) {
		return std::static_pointer_cast<ValueBool>(a)->GetValue() ==
			   std::static_pointer_cast<ValueBool>(b)->GetValue();
	}
	if (IsNumber(a)) {
		return std::static_pointer_cast<ValueNumber>(a)->GetValue() ==
			   std::static_pointer_cast<ValueNumber>(b)->GetValue();
	}
	if (IsString(a)) {
		return std::static_pointer_cast<ValueString>(a)->GetValue() ==
			   std::static_pointer_cast<ValueString>(b)->GetValue();
	}
	if (IsNull(a)) {
		return true;
	}
	return false;
}

bool ValueTool::More(std::shared_ptr<Value> a, std::shared_ptr<Value> b) {
	if (a->GetType() != b->GetType()) {
		return false;
	}
	if (IsNumber(a)) {
		return std::static_pointer_cast<ValueNumber>(a)->GetValue() >
			   std::static_pointer_cast<ValueNumber>(b)->GetValue();
	}
	return false;
}

bool ValueTool::IsInteger(std::shared_ptr<Value> value) {
	if (!IsNumber(value)) {
		return false;
	}
	auto d = std::static_pointer_cast<ValueNumber>(value)->GetValue();
	auto ll = static_cast<long long>(d);
	return (static_cast<double>(ll) == d);
}
