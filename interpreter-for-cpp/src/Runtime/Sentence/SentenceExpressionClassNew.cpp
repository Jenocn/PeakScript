#include "SentenceExpressionClassNew.h"
#include "../ClassTemplate.h"
#include "../Value/ValueClassInstance.h"

using namespace peak::interpreter;

SentenceExpressionClassNew::SentenceExpressionClassNew(const std::string& className, const std::vector<std::shared_ptr<SentenceExpression>>& args)
	: _className(className), _args(args) {
}
ExecuteResult SentenceExpressionClassNew::Execute(std::shared_ptr<Space> space) {
	auto classTemplate = space->FindClassTemplate(_className);
	if (!classTemplate) {
		return ExecuteResult::Failed;
	}

	std::vector<std::shared_ptr<Value>> tempArgs;
	tempArgs.reserve(_args.size());
	for (auto i = 0u; i < _args.size(); ++i) {
		auto arg = _args[i];
		if (!IsSuccess(arg->Execute(space))) {
			return ExecuteResult::Failed;
		}
		tempArgs.emplace_back(arg->GetValue());
	}

	auto value = std::shared_ptr<ValueClassInstance>(new ValueClassInstance(classTemplate));
	if (!value->ExecuteConstruct(tempArgs)) {
		return ExecuteResult::Failed;
	}
	SetValue(value);
	return ExecuteResult::Successed;
}