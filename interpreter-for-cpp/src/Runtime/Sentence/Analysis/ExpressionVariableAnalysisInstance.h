#include "IExpressionVariableAnalysis.h"

namespace peak::interpreter {
class ExpressionVariableAnalysisName : public IExpressionVariableAnalysis {
public:
	ExpressionVariableAnalysisName(const std::string& name);
	virtual std::shared_ptr<Variable> Execute(std::shared_ptr<Space> space);
	void SetName(const std::string& name);

private:
	std::string _name;
};

class ExpressionVariableAnalysisArrayItem : public IExpressionVariableAnalysis {
public:
	ExpressionVariableAnalysisArrayItem(std::shared_ptr<Value> valueArray, std::shared_ptr<SentenceExpression> indexExpression);
	virtual std::shared_ptr<Variable> Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<Value> _valueArray{nullptr};
	std::shared_ptr<SentenceExpression> _indexExpression{nullptr};
};
} // namespace peak::interpreter