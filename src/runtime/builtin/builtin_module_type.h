#pragma once

#include "runtime/module.h"

namespace peak {

class BuiltModuleType {
public:
    static std::shared_ptr<Module> CreateModule();
};

}