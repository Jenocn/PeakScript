/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpressionMath.h"

namespace peak::interpreter {

class IValueCalculate;

class SentenceExpressionSelfAssign : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::SelfAssign; }
};
} // namespace peak::interpreter