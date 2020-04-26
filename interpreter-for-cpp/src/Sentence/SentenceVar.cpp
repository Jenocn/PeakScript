
#include "SentenceVar.h"
#include "SentenceExpression.h"
#include "../Variable.h"

using namespace peak::interpreter;

SentenceVar::SentenceVar(const std::string& name, std::shared_ptr<SentenceExpression> expression)
	: _expression(expression) {
	_variable = std::shared_ptr<Variable>(new Variable(name));
}

bool SentenceVar::Execute(std::shared_ptr<Space> space) {
	if (_expression) {
		if (!_expression->Execute(space)) {
			return false;
		}
		_variable->SetValue(_expression->GetValue());
	}
	return space->AddVariable(_variable);
}