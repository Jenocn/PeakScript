#include "ValueCalculateInstance.h"
#include "ValueTool.h"

using namespace peak::interpreter;

std::shared_ptr<Value> ValueCalculateAdd::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	if (ValueTool::IsString(left) || ValueTool::IsString(right)) {
		return std::shared_ptr<Value>(new ValueString(ValueTool::ToString(left) + ValueTool::ToString(right)));
	}
	if (ValueTool::IsNumber(left) && ValueTool::IsNumber(right)) {
		return std::shared_ptr<Value>(new ValueNumber(
			std::static_pointer_cast<ValueNumber>(left)->GetValue() +
			std::static_pointer_cast<ValueNumber>(right)->GetValue()));
	}
	return nullptr;
}
std::shared_ptr<Value> ValueCalculateSub::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	if (ValueTool::IsNumber(left) && ValueTool::IsNumber(right)) {
		return std::shared_ptr<Value>(new ValueNumber(
			std::static_pointer_cast<ValueNumber>(left)->GetValue() -
			std::static_pointer_cast<ValueNumber>(right)->GetValue()));
	}
	return nullptr;
}
std::shared_ptr<Value> ValueCalculateMul::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	if (ValueTool::IsNumber(left) && ValueTool::IsNumber(right)) {
		return std::shared_ptr<Value>(new ValueNumber(
			std::static_pointer_cast<ValueNumber>(left)->GetValue() *
			std::static_pointer_cast<ValueNumber>(right)->GetValue()));
	}
	return nullptr;
}
std::shared_ptr<Value> ValueCalculateDiv::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	if (ValueTool::IsNumber(left) && ValueTool::IsNumber(right)) {
		return std::shared_ptr<Value>(new ValueNumber(
			std::static_pointer_cast<ValueNumber>(left)->GetValue() /
			std::static_pointer_cast<ValueNumber>(right)->GetValue()));
	}
	return nullptr;
}
std::shared_ptr<Value> ValueCalculateMod::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	if (ValueTool::IsNumber(left) && ValueTool::IsNumber(right)) {
		return std::shared_ptr<Value>(new ValueNumber(static_cast<double>(
			static_cast<long long>(std::static_pointer_cast<ValueNumber>(left)->GetValue()) %
			static_cast<long long>(std::static_pointer_cast<ValueNumber>(right)->GetValue()))));
	}
	return nullptr;
}

std::shared_ptr<Value> ValueCalculateSame::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::Equal(left, right)));
}
std::shared_ptr<Value> ValueCalculateNotSame::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	return std::shared_ptr<Value>(new ValueBool(!ValueTool::Equal(left, right)));
}
std::shared_ptr<Value> ValueCalculateMore::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::More(left, right)));
}
std::shared_ptr<Value> ValueCalculateSameOrMore::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::More(left, right) || ValueTool::Equal(left, right)));
}
std::shared_ptr<Value> ValueCalculateLess::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::More(right, left)));
}
std::shared_ptr<Value> ValueCalculateSameOrLess::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::More(right, left) || ValueTool::Equal(right, left)));
}

std::shared_ptr<Value> ValueCalculateLogicAnd::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	return std::shared_ptr<ValueBool>(new ValueBool(ValueTool::ToLogic(left) && ValueTool::ToLogic(right)));
}
std::shared_ptr<Value> ValueCalculateLogicOr::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) const {
	return std::shared_ptr<ValueBool>(new ValueBool(ValueTool::ToLogic(left) || ValueTool::ToLogic(right)));
}