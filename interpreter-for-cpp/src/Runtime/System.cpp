#include "System.h"
#include "Space.h"
#include "Value/ValueTool.h"
#include "Variable.h"

using namespace peak::interpreter;

System::BuiltIn::BuiltIn() {

	auto func_print = [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		std::string ret = "";
		for (auto arg : args) {
			ret += ValueTool::ToString(arg);
		}
		Echo(ret);
		return ValueNull::DEFAULT_VALUE;
	};
	auto value_print = std::shared_ptr<ValueFunction>(new ValueFunction(func_print));
	auto variable_print = std::shared_ptr<Variable>(new Variable("print", VariableAttribute::Const, value_print));
	variables.emplace(variable_print->GetName(), variable_print);

	auto func_type = [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		return std::shared_ptr<Value>(new ValueString(ValueTool::ToTypeString(args[0])));
	};
	auto value_type = std::shared_ptr<ValueFunction>(new ValueFunction(func_type));
	auto variable_type = std::shared_ptr<Variable>(new Variable("type", VariableAttribute::Const, value_type));
	variables.emplace(variable_type->GetName(), variable_type);
}

System::BuiltIn System::_buildIn;

std::function<void(const std::string&)> System::_funcEcho = [](const std::string& msg) {
	std::cout << msg << std::endl;
};

void System::LocateEcho(std::function<void(const std::string&)> func) {
	_funcEcho = func;
}
void System::Echo(const std::string& message) {
	_funcEcho(message);
}
std::shared_ptr<Variable> System::FindVariable(const std::string& name) {
	auto ite = _buildIn.variables.find(name);
	if (ite != _buildIn.variables.end()) {
		return ite->second;
	}
	return nullptr;
}
