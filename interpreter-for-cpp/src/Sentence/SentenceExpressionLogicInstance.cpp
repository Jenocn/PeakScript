#include "SentenceExpressionLogicInstance.h"
#include "../Value/ValueTool.h"

using namespace peak::interpreter;

std::shared_ptr<Value> SentenceExpressionLogicAnd::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	return std::shared_ptr<ValueBool>(new ValueBool(ValueTool::ToLogic(left) && ValueTool::ToLogic(right)));
}
std::shared_ptr<Value> SentenceExpressionLogicOr::Calculate(std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
	return std::shared_ptr<ValueBool>(new ValueBool(ValueTool::ToLogic(left) || ValueTool::ToLogic(right)));
}
