#include "builtin_module_strings.h"
#include "base/error_logger.h"
#include "runtime/space.h"
#include "runtime/variable.h"
#include "runtime/value/value_tool.h"

using namespace peak;

std::shared_ptr<Module> BuiltModuleStrings::CreateModule() {
    auto _InsertConst = [](std::shared_ptr<Space> space, const std::string& name, std::shared_ptr<Value> value) {
        space->AddVariable(std::make_shared<Variable>(name, VariableAttribute::Const, value));
    };
    auto _InsertFunction = [_InsertConst](std::shared_ptr<Space> space, const std::string& name, std::size_t paramSize, ValueFunction::FunctionType func) {
        _InsertConst(space, name, std::make_shared<ValueFunction>(paramSize, func));
    };

    auto space = std::make_shared<Space>(SpaceType::None);
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

    return std::make_shared<Module>(space);
}
