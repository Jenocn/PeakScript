#include "builtin_function.h"
#include "space.h"
#include "system.h"
#include "value/value_tool.h"
#include "variable.h"

using namespace peak;

BuiltInFunction* BuiltInFunction::GetInstance() {
	static BuiltInFunction _ins;
	return &_ins;
}

std::shared_ptr<Variable> BuiltInFunction::FindVariable(const std::string& name) const {
	auto ite = _variables.find(name);
	if (ite != _variables.end()) {
		return ite->second;
	}
	return nullptr;
}

BuiltInFunction::BuiltInFunction() {
	auto _Emplace = [this](const std::string& name, std::size_t paramSize, ValueFunction::FunctionType func) {
		auto value = std::make_shared<ValueFunction>(paramSize, func);
		auto variable = std::make_shared<Variable>(name, VariableAttribute::Const, value);
		_variables.emplace(name, variable);
	};

	// print
	_Emplace("print", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		std::string ret = "";
		for (auto arg : args) {
			ret += ValueTool::ToString(arg.get());
		}
		System::Echo(ret);
		return ValueNull::DEFAULT_VALUE;
	});
	// type
	_Emplace("type", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		return std::make_shared<ValueString>(ValueTool::ToTypeString(args[0].get()));
	});
	// is_null
	_Emplace("is_null", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsNull(arg.get());
		}
		return std::make_shared<ValueBool>(ret);
	});
	// is_number
	_Emplace("is_number", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsNumber(arg.get());
		}
		return std::make_shared<ValueBool>(ret);
	});
	// is_bool
	_Emplace("is_bool", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsBool(arg.get());
		}
		return std::make_shared<ValueBool>(ret);
	});
	// is_string
	_Emplace("is_string", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsString(arg.get());
		}
		return std::make_shared<ValueBool>(ret);
	});
	// is_array
	_Emplace("is_array", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsArray(arg.get());
		}
		return std::make_shared<ValueBool>(ret);
	});
	// is_function
	_Emplace("is_function", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsFunction(arg.get());
		}
		return std::make_shared<ValueBool>(ret);
	});
	// is_object
	_Emplace("is_object", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		bool ret = true;
		for (auto arg : args) {
			ret &= ValueTool::IsObject(arg.get());
		}
		return std::make_shared<ValueBool>(ret);
	});
	// len
	_Emplace("len", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		auto value = args[0];
		if (ValueTool::IsArray(value.get())) {
			return std::make_shared<ValueNumber>(static_cast<double>(std::static_pointer_cast<ValueArray>(value)->GetArray().size()));
		} else if (ValueTool::IsString(value.get())) {
			return std::make_shared<ValueNumber>(static_cast<double>(std::static_pointer_cast<ValueString>(value)->GetValue().length()));
		}
		return ValueNull::DEFAULT_VALUE;
	});
	// to_string
	_Emplace("to_string", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		auto value = args[0];
		return std::make_shared<ValueString>(ValueTool::ToString(value.get()));
	});
	// to_number
	_Emplace("to_number", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
		if (args.empty()) {
			return nullptr;
		}
		auto value = args[0];
		if (!ValueTool::IsString(value.get())) {
			return nullptr;
		}
		return std::make_shared<ValueNumber>(std::atof(std::static_pointer_cast<ValueString>(value)->GetValue().c_str()));
	});
}

