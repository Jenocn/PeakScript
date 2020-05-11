/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "../SentenceExpression.h"

namespace peak::interpreter {
class IExpressionVariableAnalysis {
public:
	virtual std::shared_ptr<Variable> Execute(std::shared_ptr<Space> space) = 0;
};
} // namespace peak::interpreter