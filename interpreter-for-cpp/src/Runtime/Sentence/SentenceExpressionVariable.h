/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpression.h"

namespace peak { 
namespace interpreter {

class Variable;
class IExpressionVariableAnalysis;

class SentenceExpressionVariable : public SentenceExpression {
public:
	SentenceExpressionVariable(std::shared_ptr<IExpressionVariableAnalysis> variableAnalysis);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::Variable; }

	std::shared_ptr<Variable> GetVariable() const;

private:
	std::shared_ptr<IExpressionVariableAnalysis> _analysis{nullptr};
	std::shared_ptr<Variable> _variable{nullptr};
};
} // namespace interpreter
} // namespace peak