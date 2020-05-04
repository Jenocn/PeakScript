/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include "SentenceExpressionValue.h"
#include <vector>

namespace peak::interpreter {
class SentenceExpressionValueArrayItem : public SentenceExpressionValue {
public:
	SentenceExpressionValueArrayItem(const std::string& name, const std::vector<std::shared_ptr<SentenceExpression>>& indexExpression);
	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

private:
	std::string _name;
	std::vector<std::shared_ptr<SentenceExpression>> _indexExpressionVec;
};
} // namespace peak::interpreter