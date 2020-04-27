
#include "../src/Runtime/Sentence/SentenceBlock.h"
#include "../src/Runtime/Sentence/SentenceExpression.h"
#include "../src/Runtime/Sentence/SentenceExpressionArithmeticInstance.h"
#include "../src/Runtime/Sentence/SentenceExpressionValue.h"
#include "../src/Runtime/Sentence/SentenceExpressionVariable.h"
#include "../src/Runtime/Sentence/SentenceVar.h"
#include "../src/Runtime/Value/ValueTool.h"
#include "../src/Runtime/Variable.h"

#include "../src/Grammar/Grammar.h"
#include "../src/Grammar/ParseTool.h"

#include <iostream>

using namespace peak::interpreter;

int main(int argc, char** argv) {
	std::shared_ptr<Space> space{new Space(SpaceType::None)};

	std::string src = "var num=\"Hello World!\"  ;  \n set num2 is \"Hello Peak!\"  ;  ";
	std::size_t pos = 0;
	std::string temp;

	auto ret = std::move(ParseTool::Load(src));
	for (auto sen : ret) {
		if (!Sentence::IsSuccess(sen->Execute(space))) {
			std::cout << "error" << std::endl;
		}
	}
	auto num2 = space->FindVariable("num");
	if (num2) {
		std::cout << ValueTool::ToString(num2->GetValue()) << std::endl;
	}

	return 0;
}