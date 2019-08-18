#pragma once

#include "vm_context.hpp"
#include "vm_value.hpp"
#include "function.hpp"

#define PARSER_CONTEXT_VAR_NAME "__cuttle_parser_context"

namespace cuttle {
    namespace lang {
        void register_lang_parser_cutvm_functions(vm::context_t &context);
    }
}