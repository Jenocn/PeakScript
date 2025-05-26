#include "builtin_module_file.h"
#include "base/error_logger.h"
#include "runtime/space.h"
#include "runtime/variable.h"
#include "runtime/value/value_tool.h"
#include "runtime/system.h"

using namespace peak;

std::shared_ptr<Module> BuiltModuleFile::CreateModule() {
    auto _InsertConst = [](std::shared_ptr<Space> space, const std::string& name, std::shared_ptr<Value> value) {
        space->AddVariable(std::make_shared<Variable>(name, VariableAttribute::Const, value));
    };
    auto _InsertFunction = [_InsertConst](std::shared_ptr<Space> space, const std::string& name, std::size_t paramSize, ValueFunction::FunctionType func) {
        _InsertConst(space, name, std::make_shared<ValueFunction>(paramSize, func));
    };

    auto space = std::make_shared<Space>(SpaceType::None);

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

    return std::make_shared<Module>(space);
}
