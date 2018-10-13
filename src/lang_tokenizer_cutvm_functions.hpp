#pragma once

#include "vm_context.hpp"
#include "vm_value.hpp"
#include "tokenizer_config.hpp"

#define TOKENIZER_CONFIG_VAR_NAME "__cuttle_tokenizer_config"

namespace cuttle {
    namespace lang {
        void register_lang_tokenizer_cutvm_functions(vm::context_t &context);
    }
}