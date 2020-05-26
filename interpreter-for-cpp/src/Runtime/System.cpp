#include "System.h"
#include "Space.h"
#include "Value/ValueTool.h"
#include "Variable.h"

using namespace peak::interpreter;

System::BuiltIn::BuiltIn() {
	auto _Emplace = [this](const std::string& name, std::size_t paramSize, ValueFunction::FunctionType func) {
		auto value = std::shared_ptr<ValueFunction>(new ValueFunction(paramSize, func));
		auto variable = std::shared_ptr<Variable>(new Variable(name, VariableAttribute::Const, value));
		variables.emplace(name, variable);
	};

	// print
	_Emplace("print", 1, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		std::string ret = "";
		for (auto arg : args) {
			ret += ValueTool::ToString(arg);
		}
		Echo(ret);
		return ValueNull::DEFAULT_VALUE;
	});
	// type
	_Emplace("type", 1, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		return std::shared_ptr<Value>(new ValueString(ValueTool::ToTypeString(args[0])));
	});
	// is_null
	_Emplace("is_null", 1, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsNull(arg);
		}
		return std::shared_ptr<Value>(new ValueBool(ret));
	});
	// is_number
	_Emplace("is_number", 1, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsNumber(arg);
		}
		return std::shared_ptr<Value>(new ValueBool(ret));
	});
	// is_bool
	_Emplace("is_bool", 1, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsBool(arg);
		}
		return std::shared_ptr<Value>(new ValueBool(ret));
	});
	// is_string
	_Emplace("is_string", 1, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsString(arg);
		}
		return std::shared_ptr<Value>(new ValueBool(ret));
	});
	// is_array
	_Emplace("is_array", 1, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsArray(arg);
		}
		return std::shared_ptr<Value>(new ValueBool(ret));
	});
	// is_function
	_Emplace("is_function", 1, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsFunction(arg);
		}
		return std::shared_ptr<Value>(new ValueBool(ret));
	});
	// len
	_Emplace("len", 1, [this](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space> s) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		auto value = args[0];
		if (ValueTool::IsArray(value)) {
			return std::shared_ptr<Value>(new ValueNumber(std::static_pointer_cast<ValueArray>(value)->GetArray().size()));
		} else if (ValueTool::IsString(value)) {
			return std::shared_ptr<Value>(new ValueNumber(std::static_pointer_cast<ValueString>(value)->GetValue().length()));
		}
		return ValueNull::DEFAULT_VALUE;
	});
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
