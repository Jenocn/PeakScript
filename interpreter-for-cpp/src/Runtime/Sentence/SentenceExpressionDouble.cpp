#include "SentenceExpressionDouble.h"
#include "../Value/IValueCalculate.h"
#include "../Value/ValueTool.h"
#include "../Variable.h"
#include "SentenceExpressionVariable.h"

using namespace peak::interpreter;

SentenceExpressionDouble::SentenceExpressionDouble(std::shared_ptr<SentenceExpression> variableExpresison, IValueCalculate* calculate, bool last)
	: _variableExpresison(variableExpresison), _calculate(calculate), _bLast(last) {
}

ExecuteResult SentenceExpressionDouble::Execute(std::shared_ptr<Space> space) {
	if (!_variableExpresison || !_calculate) {
		return ExecuteResult::Failed;
	}
	if (_variableExpresison->GetExpressionType() != ExpressionType::Variable) {
		return ExecuteResult::Failed;
	}
	if (!IsSuccess(_variableExpresison->Execute(space))) {
		return ExecuteResult::Failed;
	}
	auto variable = std::static_pointer_cast<SentenceExpressionVariable>(_variableExpresison)->GetVariable();
	if (!variable) {
		return ExecuteResult::Failed;
	}
	auto value = _variableExpresison->GetValue();
	if (!ValueTool::IsNumber(value)) {
		return ExecuteResult::Failed;
	}
	auto ret = _calculate->Calculate(value, std::shared_ptr<Value>(new ValueNumber(1)));
	if (!ret) {
		return ExecuteResult::Failed;
	}
	if (!variable->SetValue(ret)) {
		return ExecuteResult::Failed;
	}
	SetValue(_bLast ? value : ret);
	return ExecuteResult::Successed;
}