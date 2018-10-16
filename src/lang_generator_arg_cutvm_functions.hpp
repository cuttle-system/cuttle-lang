#pragma once

#include "vm_context.hpp"
#include "vm_value.hpp"
#include "generator_config.hpp"

#define PRESENTER_PARAMS_VAR_NAME "__cuttle_presenter_params"
#define PRESENTER_PARAMS_ARGI_VAR_NAME "cuttle_presenter_params_argi"

namespace cuttle {
    namespace lang {
        void register_lang_generator_arg_cutvm_functions(vm::context_t &context);
    }
}