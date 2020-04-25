
#include "../src/SentenceBlock.h"
#include "../src/SentenceExpression.h"
#include "../src/SentenceExpressionValue.h"
#include "../src/SentenceExpressionVariable.h"
#include "../src/SentenceVar.h"
#include "../src/ValueNumber.h"

#include <iostream>

using namespace peak::interpreter;

int main(int argc, char** argv) {
	std::shared_ptr<Space> space{new Space()};

	auto number = std::shared_ptr<ValueNumber>(new ValueNumber());
	number->SetValue(999);

{
	SentenceBlock block;
	block.Push(std::shared_ptr<Sentence>(new SentenceVar("temp", std::shared_ptr<SentenceExpressionValue>(new SentenceExpressionValue(number)))));
	block.Push(std::shared_ptr<Sentence>(new SentenceVar("abc", std::shared_ptr<SentenceExpressionVariable>(new SentenceExpressionVariable("temp")))));
	if (!block.Execute(space)) {
		std::cout << "error" << std::endl;
	}
}

	std::cout << number.use_count() << std::endl;
	std::cout << "end" << std::endl;

	return 0;
}