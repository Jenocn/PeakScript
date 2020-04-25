
#include "../src/SentenceBlock.h"
#include "../src/SentenceVarFromName.h"
#include "../src/SentenceVarFromValue.h"
#include "../src/ValueNumber.h"

#include <iostream>

using namespace peak::interpreter;

class A {
public:
	A() {
		std::cout << "A" << std::endl;
	}
	~A() {
		std::cout << "~A" << std::endl;
	}
};

int main(int argc, char** argv) {
	std::shared_ptr<Space> space{new Space()};
	SentenceBlock block;

	auto number = new ValueNumber();
	number->SetValue(999);
	std::shared_ptr<Sentence> sentence{new SentenceVarFromValue("temp", std::shared_ptr<Value>(number))};
	block.Push(sentence);
	block.Execute(space);

	std::cout << "end";

	return 0;
}