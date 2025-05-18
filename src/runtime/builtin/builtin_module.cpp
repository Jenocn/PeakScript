#include "builtin_module.h"
#include "runtime/space.h"
#include "runtime/module.h"
#include "runtime/variable.h"
#include "runtime/value/value_tool.h"
#include "runtime/system.h"

using namespace peak;

BuiltinModule* BuiltinModule::GetInstance() {
	static BuiltinModule _ins;
	return &_ins;
}
std::shared_ptr<Module> BuiltinModule::FindModule(const std::string& name) const {
	auto ite = _modules.find(name);
	if (ite != _modules.end()) {
		return ite->second;
	}
	return nullptr;
}
BuiltinModule::BuiltinModule() {
	auto _InsertConst = [](std::shared_ptr<Space> space, const std::string& name, std::shared_ptr<Value> value) {
		space->AddVariable(std::make_shared<Variable>(name, VariableAttribute::Const, value));
	};
	auto _InsertFunction = [_InsertConst](std::shared_ptr<Space> space, const std::string& name, std::size_t paramSize, ValueFunction::FunctionType func) {
		_InsertConst(space, name, std::make_shared<ValueFunction>(paramSize, func));
	};
	auto _InsertModule = [this](const std::string& name) -> std::shared_ptr<Space> {
		auto space = std::make_shared<Space>(SpaceType::None);
		_modules.emplace(name, std::make_shared<Module>(space));
		return space;
	};


	{
		auto space = _InsertModule("string");
		_InsertFunction(space, "len", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsString(args[0].get())) {
				return std::make_shared<ValueNumber>(static_cast<double>(std::static_pointer_cast<ValueString>(args[0])->GetValue().size()));
			}
			return nullptr;
		});
		_InsertFunction(space, "substr", 3, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsString(args[0].get()) && ValueTool::IsInteger(args[1].get())) {
				const auto& ret = std::static_pointer_cast<ValueString>(args[0])->GetValue();
				double argsIndex = std::static_pointer_cast<ValueNumber>(args[1])->GetValue();
				auto index = static_cast<std::size_t>(argsIndex);
				if (argsIndex >= 0 && index <= ret.size()) {
					std::size_t count = std::string::npos;
					if (ValueTool::IsInteger(args[2].get())) {
						count = static_cast<std::size_t>(std::static_pointer_cast<ValueNumber>(args[2])->GetValue());
					}
					return std::make_shared<ValueString>(ret.substr(index, count));
				}
			}
			return nullptr;
		});
		_InsertFunction(space, "at", 2, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsString(args[0].get()) && ValueTool::IsInteger(args[1].get())) {
				const auto& ret = std::static_pointer_cast<ValueString>(args[0])->GetValue();
				auto argsIndex = std::static_pointer_cast<ValueNumber>(args[1])->GetValue();
				auto index = static_cast<std::size_t>(argsIndex);
				if (argsIndex >= 0 && index < ret.size()) {
					return std::make_shared<ValueString>(std::string(1, ret.at(index)));
				}
			}
			return nullptr;
		});
		_InsertFunction(space, "split", 2, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsString(args[0].get()) && ValueTool::IsString(args[1].get())) {
				const auto& str = std::static_pointer_cast<ValueString>(args[0])->GetValue();
				const auto& sp = std::static_pointer_cast<ValueString>(args[1])->GetValue();
				auto ret = std::make_shared<ValueArray>();
				if (sp.empty()) {
					for (auto i = 0u; i < str.size(); ++i) {
						ret->EmplaceBack(std::make_shared<ValueString>(std::string(1, str[i])));
					}
				} else {
					auto posL = 0u;
					auto pos = 0u;
					while (pos < str.size()) {
						if (pos + sp.size() > str.size()) {
							break;
						}
						auto i = 0u;
						while (i < sp.size() && sp[i] == str[pos + i]) {
							++i;
						}
						if (i == sp.size()) {
							auto count = pos - posL;
							if (count > 0) {
								ret->EmplaceBack(std::make_shared<ValueString>(str.substr(posL, count)));
							}
							pos = pos + i;
							posL = pos;
						} else {
							++pos;
						}
					}
					if (posL < str.size()) {
						ret->EmplaceBack(std::make_shared<ValueString>(str.substr(posL)));
					}
				}
				return ret;
			}
			return nullptr;
		});
	}


	{
		auto space = _InsertModule("array");
		_InsertFunction(space, "len", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsArray(args[0].get())) {
				return std::make_shared<ValueNumber>(static_cast<double>(std::static_pointer_cast<ValueArray>(args[0])->GetArray().size()));
			}
			return nullptr;
		});
		_InsertFunction(space, "append", 2, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsArray(args[0].get())) {
				auto ret = std::static_pointer_cast<ValueArray>(args[0]);
				ret->EmplaceBack(args[1]);
				return args[0];
			}
			return nullptr;
		});
		_InsertFunction(space, "insert", 3, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsArray(args[0].get()) && ValueTool::IsInteger(args[1].get())) {
				auto& ret = std::static_pointer_cast<ValueArray>(args[0])->GetArray();
				auto argIndex = std::static_pointer_cast<ValueNumber>(args[1])->GetValue();
				if (argIndex >= 0) {
					auto index = std::min(static_cast<long long>(argIndex), static_cast<long long>(ret.size()));
					ret.insert(ret.begin() + index, std::make_shared<Variable>("", VariableAttribute::None, args[2]));
					return args[0];
				}
			}
			return nullptr;
		});
		_InsertFunction(space, "remove_from", 3, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsArray(args[0].get()) && ValueTool::IsInteger(args[1].get()) && ValueTool::IsInteger(args[2].get())) {
				auto& ret = std::static_pointer_cast<ValueArray>(args[0])->GetArray();
				auto index = static_cast<long long>(std::static_pointer_cast<ValueNumber>(args[1])->GetValue());
				if (index >= 0 && index < static_cast<long long>(ret.size())) {
					auto count = static_cast<long long>(std::static_pointer_cast<ValueNumber>(args[2])->GetValue());
					count = std::min(count, static_cast<long long>(ret.size()) - index);
					if (count >= 0) {
						ret.erase(ret.begin() + index, ret.begin() + index + count);
						return args[0];
					}
				}
			}
			return nullptr;
		});
		_InsertFunction(space, "remove_at", 2, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsArray(args[0].get()) && ValueTool::IsInteger(args[1].get())) {
				auto& ret = std::static_pointer_cast<ValueArray>(args[0])->GetArray();
				auto index = static_cast<long long>(std::static_pointer_cast<ValueNumber>(args[1])->GetValue());
				if (index >= 0 && index < static_cast<long long>(ret.size())) {
					ret.erase(ret.begin() + index);
					return args[0];
				}
			}
			return nullptr;
		});
		_InsertFunction(space, "remove", 2, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (ValueTool::IsArray(args[0].get())) {
				auto& ret = std::static_pointer_cast<ValueArray>(args[0])->GetArray();
				auto target = args[1];
				auto ite = std::find_if(ret.begin(), ret.end(), [target](std::shared_ptr<peak::Variable> item) {
					return ValueTool::Equal(target.get(), item->GetValue().get());
				});
				if (ite != ret.end()) {
					ret.erase(ite);
				}
				return args[0];
			}
			return nullptr;
		});
	}


	{
		auto space = _InsertModule("time");
		_InsertFunction(space, "get_tick", 0, [](const std::vector<std::shared_ptr<Value>>&, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			auto now = std::chrono::system_clock::now();
			auto duration = now.time_since_epoch();
			auto tick = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
			return std::make_shared<ValueNumber>(static_cast<double>(tick));
		});
		_InsertFunction(space, "get_utc_time", 0, [](const std::vector<std::shared_ptr<Value>>&, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			auto now = std::chrono::system_clock::now();
			std::time_t now_time = std::chrono::system_clock::to_time_t(now);
			std::tm now_tm;

#if defined(_MSC_VER)
			if (gmtime_s(&now_tm, &now_time) != 0) {
				return nullptr;
			}
#else
			if (!gmtime_r(&now_time, &now_tm)) {
				return nullptr;
			}
#endif
			auto year = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_year + 1900));
			auto month = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_mon + 1));
			auto day = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_mday));
			auto hour = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_hour));
			auto minute = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_min));
			auto second = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_sec));

			auto ret = std::make_shared<ValueObject>();
			auto retSpace = ret->GetSpace();
			retSpace->AddVariable(std::make_shared<Variable>("year", VariableAttribute::None, year));
			retSpace->AddVariable(std::make_shared<Variable>("month", VariableAttribute::None, month));
			retSpace->AddVariable(std::make_shared<Variable>("day", VariableAttribute::None, day));

			retSpace->AddVariable(std::make_shared<Variable>("hour", VariableAttribute::None, hour));
			retSpace->AddVariable(std::make_shared<Variable>("minute", VariableAttribute::None, minute));
			retSpace->AddVariable(std::make_shared<Variable>("second", VariableAttribute::None, second));
			return ret;
		});
		_InsertFunction(space, "get_local_time", 0, [](const std::vector<std::shared_ptr<Value>>&, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			auto now = std::chrono::system_clock::now();
			std::time_t now_time = std::chrono::system_clock::to_time_t(now);
			std::tm now_tm;

#if defined(_MSC_VER)
			if (localtime_s(&now_tm, &now_time) != 0) {
				return nullptr;
			}
#else
			if (!localtime_r(&now_time, &now_tm)) {
				return nullptr;
			}
#endif
			auto year = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_year + 1900));
			auto month = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_mon + 1));
			auto day = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_mday));
			auto hour = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_hour));
			auto minute = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_min));
			auto second = std::make_shared<ValueNumber>(static_cast<double>(now_tm.tm_sec));

			auto ret = std::make_shared<ValueObject>();
			auto retSpace = ret->GetSpace();
			retSpace->AddVariable(std::make_shared<Variable>("year", VariableAttribute::None, year));
			retSpace->AddVariable(std::make_shared<Variable>("month", VariableAttribute::None, month));
			retSpace->AddVariable(std::make_shared<Variable>("day", VariableAttribute::None, day));

			retSpace->AddVariable(std::make_shared<Variable>("hour", VariableAttribute::None, hour));
			retSpace->AddVariable(std::make_shared<Variable>("minute", VariableAttribute::None, minute));
			retSpace->AddVariable(std::make_shared<Variable>("second", VariableAttribute::None, second));
			return ret;
		});
	}

	{
		auto space = _InsertModule("console");
		_InsertFunction(space, "input", 0, [](const std::vector<std::shared_ptr<Value>>&, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			std::string ret;
			std::getline(std::cin, ret);
			return std::make_shared<ValueString>(ret);
		});
		_InsertFunction(space, "log", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			System::Echo(args[0]->ToString());
			return ValueNull::DEFAULT_VALUE;
		});
	}

	{
		auto space = _InsertModule("type");

		_InsertFunction(space, "get_type_string", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			return std::make_shared<ValueString>(ValueTool::ToTypeString(args[0].get()));
		});

		_InsertFunction(space, "to_string", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			return std::make_shared<ValueString>(ValueTool::ToString(args[0].get()));
		});

		_InsertFunction(space, "to_number", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			auto value = args[0];
			if (ValueTool::IsNumber(value.get())) {
				return std::make_shared<ValueNumber>(std::static_pointer_cast<ValueNumber>(value)->GetValue());
			}
			if (ValueTool::IsString(value.get())) {
				return std::make_shared<ValueNumber>(std::atof(std::static_pointer_cast<ValueString>(value)->GetValue().c_str()));
			}
			return nullptr;
		});

		_InsertFunction(space, "is_null", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			return std::make_shared<ValueBool>(ValueTool::IsNull(args[0].get()));
		});

		_InsertFunction(space, "is_number", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			return std::make_shared<ValueBool>(ValueTool::IsNumber(args[0].get()));
		});

		_InsertFunction(space, "is_bool", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			return std::make_shared<ValueBool>(ValueTool::IsBool(args[0].get()));
		});

		_InsertFunction(space, "is_string", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			return std::make_shared<ValueBool>(ValueTool::IsString(args[0].get()));
		});

		_InsertFunction(space, "is_array", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			return std::make_shared<ValueBool>(ValueTool::IsArray(args[0].get()));
		});

		_InsertFunction(space, "is_function", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			return std::make_shared<ValueBool>(ValueTool::IsFunction(args[0].get()));
		});

		_InsertFunction(space, "is_object", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			return std::make_shared<ValueBool>(ValueTool::IsObject(args[0].get()));
		});
	}

	{
		auto space = _InsertModule("file");
		_InsertFunction(space, "load_text", 1, [](const std::vector<std::shared_ptr<Value>>& args, std::shared_ptr<Space>) -> std::shared_ptr<Value> {
			if (!ValueTool::IsString(args[0].get())) {
				return nullptr;
			}
			const auto& filename = std::static_pointer_cast<ValueString>(args[0])->GetValue();
			auto path = std::filesystem::absolute(filename); 
			if (!std::filesystem::exists(path)) {
				return nullptr;
			}
			return std::make_shared<ValueString>(System::LoadText(path.string()));
		});
	}
}