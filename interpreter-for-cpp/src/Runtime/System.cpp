#include "System.h"
#include "Space.h"
#include "Value/ValueTool.h"
#include "Variable.h"

using namespace peak::interpreter;

System::BuiltIn::BuiltIn() {

	{
		// print
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
	}
	{
		// type
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
	{
		// is_null
		auto func = [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
			if (args.empty()) {
				return nullptr;
			}
			bool ret = true;
			for (auto arg : args) {
				ret &= ValueTool::IsNull(arg);
			}
			return std::shared_ptr<Value>(new ValueBool(ret));
		};
		auto value = std::shared_ptr<ValueFunction>(new ValueFunction(func));
		auto variable = std::shared_ptr<Variable>(new Variable("is_null", VariableAttribute::Const, value));
		variables.emplace(variable->GetName(), variable);
	}
	{
		// is_number
		auto func = [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
			if (args.empty()) {
				return nullptr;
			}
			bool ret = true;
			for (auto arg : args) {
				ret &= ValueTool::IsNumber(arg);
			}
			return std::shared_ptr<Value>(new ValueBool(ret));
		};
		auto value = std::shared_ptr<ValueFunction>(new ValueFunction(func));
		auto variable = std::shared_ptr<Variable>(new Variable("is_number", VariableAttribute::Const, value));
		variables.emplace(variable->GetName(), variable);
	}
	{
		// is_bool
		auto func = [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
			if (args.empty()) {
				return nullptr;
			}
			bool ret = true;
			for (auto arg : args) {
				ret &= ValueTool::IsBool(arg);
			}
			return std::shared_ptr<Value>(new ValueBool(ret));
		};
		auto value = std::shared_ptr<ValueFunction>(new ValueFunction(func));
		auto variable = std::shared_ptr<Variable>(new Variable("is_bool", VariableAttribute::Const, value));
		variables.emplace(variable->GetName(), variable);
	}
	{
		// is_string
		auto func = [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
			if (args.empty()) {
				return nullptr;
			}
			bool ret = true;
			for (auto arg : args) {
				ret &= ValueTool::IsString(arg);
			}
			return std::shared_ptr<Value>(new ValueBool(ret));
		};
		auto value = std::shared_ptr<ValueFunction>(new ValueFunction(func));
		auto variable = std::shared_ptr<Variable>(new Variable("is_string", VariableAttribute::Const, value));
		variables.emplace(variable->GetName(), variable);
	}
	{
		// is_array
		auto func = [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
			if (args.empty()) {
				return nullptr;
			}
			bool ret = true;
			for (auto arg : args) {
				ret &= ValueTool::IsArray(arg);
			}
			return std::shared_ptr<Value>(new ValueBool(ret));
		};
		auto value = std::shared_ptr<ValueFunction>(new ValueFunction(func));
		auto variable = std::shared_ptr<Variable>(new Variable("is_array", VariableAttribute::Const, value));
		variables.emplace(variable->GetName(), variable);
	}
	{
		// is_function
		auto func = [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
			if (args.empty()) {
				return nullptr;
			}
			bool ret = true;
			for (auto arg : args) {
				ret &= ValueTool::IsFunction(arg);
			}
			return std::shared_ptr<Value>(new ValueBool(ret));
		};
		auto value = std::shared_ptr<ValueFunction>(new ValueFunction(func));
		auto variable = std::shared_ptr<Variable>(new Variable("is_function", VariableAttribute::Const, value));
		variables.emplace(variable->GetName(), variable);
	}
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
