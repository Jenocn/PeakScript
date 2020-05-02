
#include "../src/Grammar/ParseTool.h"
#include "../src/Runtime/Sentence/Sentence.h"
#include "../src/Runtime/Sentence/SentenceExpression.h"
#include "../src/Runtime/Sentence/SentenceExpressionVariable.h"
#include "../src/Runtime/Value/ValueTool.h"
#include "../src/Runtime/Variable.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace peak::interpreter;

std::string openFile(const std::string& filename) {
	std::ifstream in(filename.c_str(), std::ios::in | std::ios::ate);
	if (!in.is_open()) {
		return "";
	}
	std::string result;
	do {
		std::size_t size = (std::size_t)in.tellg();
		if (size == 0) {
			break;
		}
		in.seekg(std::ios::beg);
		char* buffer = new (std::nothrow) char[size];
		if (!buffer) {
			break;
		}
		memset(buffer, 0, size);
		in.read(buffer, size);
		result = buffer;
		delete[] buffer;
	} while (0);
	in.close();
	return result;
}

int main(int argc, char** argv) {
	std::shared_ptr<Space> space{new Space(SpaceType::None)};

	auto src = std::move(openFile("/Users/jenocn/Project/PeakScript/interpreter-for-cpp/test/test2.peak"));
	std::cout << src << std::endl << std::endl;

	auto ret = std::move(ParseTool::Load(src));

	for (auto sen : ret) {
		if (!Sentence::IsSuccess(sen->Execute(space))) {
			std::cout << "error" << std::endl;
		}
	}

	while (true) {
		std::cout << ">";
		std::string key;
		std::cin >> key;
		if (key == "q") {
			break;
		}
		auto v = space->FindVariable(key);
		if (v) {
			std::cout << ValueTool::ToString(v->GetValue()) << std::endl;
		}
	}

	return 0;
}