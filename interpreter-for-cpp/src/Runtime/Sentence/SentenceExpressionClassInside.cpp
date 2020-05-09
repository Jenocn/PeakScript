#include "SentenceExpressionClassInside.h"
#include "../ClassTemplate.h"
#include "../Value/ValueTool.h"
#include "SentenceExpressionClassNew.h"
#include "SentenceExpressionFunctionCall.h"
#include "SentenceExpressionValueArrayItem.h"
#include "SentenceExpressionVariable.h"

using namespace peak::interpreter;

SentenceExpressionClassInside::SentenceExpressionClassInside(const std::list<std::shared_ptr<SentenceExpression>>& insideList)
	: _insideList(insideList) {
}
ExecuteResult SentenceExpressionClassInside::Execute(std::shared_ptr<Space> space) {

	auto tempSpace = space;
	auto i = 0u;
	auto size = _insideList.size();

	auto publicSpace = space;
	std::shared_ptr<ClassTemplate> staticClass{nullptr};

	for (auto sen : _insideList) {
		staticClass = nullptr;
		switch (sen->GetExpressionType()) {
		case ExpressionType::Variable: {
			auto variableName = std::static_pointer_cast<SentenceExpressionVariable>(sen)->GetVariableName();
			auto findVariable = publicSpace->FindVariable(variableName);
			if (!findVariable) {
				staticClass = publicSpace->FindClassTemplate(variableName);
				if (!staticClass) {
					return ExecuteResult::Failed;
				}
			}
		} break;
		case ExpressionType::Function:
			if (!publicSpace->FindVariable(std::static_pointer_cast<SentenceExpressionFunctionCall>(sen)->GetFunctionName())) {
				return ExecuteResult::Failed;
			}
			break;
		case ExpressionType::ArrayItem:
			if (!publicSpace->FindVariable(std::static_pointer_cast<SentenceExpressionValueArrayItem>(sen)->GetArrayName())) {
				return ExecuteResult::Failed;
			}
			break;
		default:
			break;
		}

		if (staticClass) {
			publicSpace = staticClass->GetStaticSpace();
			tempSpace = staticClass->GetStaticSpace();
		} else {
			if (!IsSuccess(sen->Execute(tempSpace))) {
				return ExecuteResult::Failed;
			}
			auto value = sen->GetValue();
			if (i == size - 1) {
				SetValue(value);
				break;
			}

			if (!ValueTool::IsClassInstance(value)) {
				return ExecuteResult::Failed;
			}

			auto civ = std::static_pointer_cast<ValueClassInstance>(value);
			publicSpace = civ->GetPublicSpace();
			tempSpace = civ->GetSpaceOfThis();
		}

		++i;
	}

	return ExecuteResult::Successed;
}