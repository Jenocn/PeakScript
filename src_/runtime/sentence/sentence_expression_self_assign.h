/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "sentence_expression_math.h"

namespace peak { 


class IValueCalculate;

class SentenceExpressionSelfAssign : public SentenceExpressionMath {
public:
	using SentenceExpressionMath::SentenceExpressionMath;
	SentenceExpressionSelfAssign() = delete;
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);
	virtual ExpressionType GetExpressionType() const { return ExpressionType::SelfAssign; }
};

} // namespace peak