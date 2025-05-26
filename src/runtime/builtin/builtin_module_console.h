#pragma once

#include "runtime/module.h"

namespace peak {

class BuiltModuleConsole {
public:
    static std::shared_ptr<Module> CreateModule();
};

}