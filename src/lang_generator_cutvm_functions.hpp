#pragma once

#include "vm_context.hpp"
#include "vm_value.hpp"
#include "generator_config.hpp"

#define GENERATOR_CONFIG_VAR_NAME "__cuttle_generator_config"

namespace cuttle {
    namespace lang {
        void register_lang_generator_cutvm_functions(vm::context_t &context);
    }
}