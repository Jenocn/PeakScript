#pragma once

#include "runtime/module.h"

namespace peak {

class BuiltModuleFile {
public:
    static std::shared_ptr<Module> CreateModule();
};

}