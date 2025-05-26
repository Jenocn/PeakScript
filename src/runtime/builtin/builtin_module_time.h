#pragma once

#include "runtime/module.h"

namespace peak {

class BuiltModuleTime {
public:
    static std::shared_ptr<Module> CreateModule();
};

}