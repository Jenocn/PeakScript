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
	ExpressionVariableAnalysisArrayItem(std::shared_ptr<SentenceExpression> valueExpression, std::vector<std::shared_ptr<SentenceExpression>> indexExpressionVec);
	virtual std::shared_ptr<Variable> Execute(std::shared_ptr<Space> space);

private:
	std::shared_ptr<SentenceExpression> _valueExpression{nullptr};
	std::vector<std::shared_ptr<SentenceExpression>> _indexExpressionVec{nullptr};
};

} // namespace peak::interpreter