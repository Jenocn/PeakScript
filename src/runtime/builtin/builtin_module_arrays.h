#pragma once

#include "runtime/module.h"

namespace peak {

class BuiltModuleArrays {
public:
    static std::shared_ptr<Module> CreateModule();
};

}