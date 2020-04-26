#include "SentenceExpressionRelationalInstance.h"

#include "ValueTool.h"
using namespace peak::interpreter;

std::shared_ptr<Value> SentenceExpressionRelationalSame::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::Equal(left, right)));
}
std::shared_ptr<Value> SentenceExpressionRelationalNotSame::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	return std::shared_ptr<Value>(new ValueBool(!ValueTool::Equal(left, right)));
}
std::shared_ptr<Value> SentenceExpressionRelationalMore::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::More(left, right)));
}
std::shared_ptr<Value> SentenceExpressionRelationalSameOrMore::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::More(left, right) || ValueTool::Equal(left, right)));
}
std::shared_ptr<Value> SentenceExpressionRelationalLess::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::More(right, left)));
}
std::shared_ptr<Value> SentenceExpressionRelationalSameOrLess::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	return std::shared_ptr<Value>(new ValueBool(ValueTool::More(right, left) || ValueTool::Equal(right, left)));
}
