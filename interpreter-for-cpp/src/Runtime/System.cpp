#include "System.h"
#include "Space.h"
#include "Value/ValueTool.h"
#include "Variable.h"

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
