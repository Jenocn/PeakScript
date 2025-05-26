#pragma once

#include "runtime/module.h"

namespace peak {

class BuiltModuleRandom {
public:
    static std::shared_ptr<Module> CreateModule();
};

}