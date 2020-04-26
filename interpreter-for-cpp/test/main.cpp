
#include "../src/SentenceBlock.h"
#include "../src/SentenceExpression.h"
#include "../src/SentenceExpressionArithmeticInstance.h"
#include "../src/SentenceExpressionValue.h"
#include "../src/SentenceExpressionVariable.h"
#include "../src/SentenceVar.h"
#include "../src/ValueTool.h"
#include "../src/Variable.h"

#include <iostream>

using namespace peak::interpreter;

int main(int argc, char** argv) {
	std::shared_ptr<Space> space{new Space()};

	ValueString::Type();
	auto number = std::shared_ptr<Value>(new ValueNumber(999));
	SentenceBlock block;
	block.Push(std::shared_ptr<Sentence>(new SentenceVar("temp", std::shared_ptr<SentenceExpressionValue>(new SentenceExpressionValue(number)))));
	block.Push(std::shared_ptr<Sentence>(new SentenceVar("abc", std::shared_ptr<SentenceExpressionVariable>(new SentenceExpressionVariable("temp")))));
	if (!block.Execute(space)) {
		std::cout << "error" << std::endl;
	}

	auto tempSentence = std::shared_ptr<SentenceExpressionArithmetic>(new SentenceExpressionArithmeticAdd(
		std::shared_ptr<SentenceExpression>(new SentenceExpressionValue(std::shared_ptr<Value>(new ValueNumber(10)))),
		std::shared_ptr<SentenceExpression>(new SentenceExpressionValue(std::shared_ptr<Value>(new ValueNumber(20))))));
	auto varSentence = std::shared_ptr<Sentence>(new SentenceVar("value", tempSentence));
	varSentence->Execute(space);

	auto findVariable = space->FindVariable("value");
	if (findVariable) {
		std::cout << ValueTool::ToString(findVariable->GetValue()) << std::endl;
	}

	std::cout << ValueNumber::Type() << std::endl;
	std::cout << ValueString::Type() << std::endl;
	std::cout << ValueNull::Type() << std::endl;
	std::cout << ValueBool::Type() << std::endl;
	std::cout << "end" << std::endl;

	return 0;
}