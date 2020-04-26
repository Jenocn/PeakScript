#include "SentenceExpressionArithmeticInstance.h"
#include "../Value/ValueTool.h"

using namespace peak::interpreter;

std::shared_ptr<Value> SentenceExpressionArithmeticAdd::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
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
std::shared_ptr<Value> SentenceExpressionArithmeticSub::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	if (ValueTool::IsNumber(left) && ValueTool::IsNumber(right)) {
		return std::shared_ptr<Value>(new ValueNumber(
			std::static_pointer_cast<ValueNumber>(left)->GetValue() -
			std::static_pointer_cast<ValueNumber>(right)->GetValue()));
	}
	return nullptr;
}
std::shared_ptr<Value> SentenceExpressionArithmeticMul::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	if (ValueTool::IsNumber(left) && ValueTool::IsNumber(right)) {
		return std::shared_ptr<Value>(new ValueNumber(
			std::static_pointer_cast<ValueNumber>(left)->GetValue() *
			std::static_pointer_cast<ValueNumber>(right)->GetValue()));
	}
	return nullptr;
}
std::shared_ptr<Value> SentenceExpressionArithmeticDiv::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	if (ValueTool::IsNumber(left) && ValueTool::IsNumber(right)) {
		return std::shared_ptr<Value>(new ValueNumber(
			std::static_pointer_cast<ValueNumber>(left)->GetValue() /
			std::static_pointer_cast<ValueNumber>(right)->GetValue()));
	}
	return nullptr;
}
std::shared_ptr<Value> SentenceExpressionArithmeticMod::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	if (ValueTool::IsNumber(left) && ValueTool::IsNumber(right)) {
		return std::shared_ptr<Value>(new ValueNumber(
			(long long)std::static_pointer_cast<ValueNumber>(left)->GetValue() %
			(long long)std::static_pointer_cast<ValueNumber>(right)->GetValue()));
	}
	return nullptr;
}
