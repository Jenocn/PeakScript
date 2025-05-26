#include "builtin_module_type.h"
#include "base/error_logger.h"
#include "runtime/space.h"
#include "runtime/variable.h"
#include "runtime/value/value_tool.h"
#include "runtime/system.h"

using namespace peak;

std::shared_ptr<Module> BuiltModuleType::CreateModule() {
    auto _InsertConst = [](std::shared_ptr<Space> space, const std::string& name, std::shared_ptr<Value> value) {
        space->AddVariable(std::make_shared<Variable>(name, VariableAttribute::Const, value));
    };
    auto _InsertFunction = [_InsertConst](std::shared_ptr<Space> space, const std::string& name, std::size_t paramSize, ValueFunction::FunctionType func) {
        _InsertConst(space, name, std::make_shared<ValueFunction>(paramSize, func));
    };

    auto space = std::make_shared<Space>(SpaceType::None);

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

    return std::make_shared<Module>(space);
}
