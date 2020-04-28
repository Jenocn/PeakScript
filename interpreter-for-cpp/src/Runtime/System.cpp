#include "System.h"
#include <iostream>

using namespace peak::interpreter;

std::function<void(const std::string&)> System::_funcEcho = [](const std::string& msg) {
	std::cout << msg << std::endl;
};

void System::LocateEcho(std::function<void(const std::string&)> func) {
	_funcEcho = func;
}
void System::Echo(const std::string& message) {
	_funcEcho(message);
}