#pragma once

#include "vm_context.hpp"
#include "vm_value.hpp"

#define PARSER_CONTEXT_CONFIG_ARRAY_DEFAULT_VALUES cuttle::vm::value_t{cuttle::lang::PARSER_CONTEXT_CONFIG_TYPE, \
    { \
    vm_context.gc.add( \
        new cuttle::vm::array_t{ \
            {{cuttle::vm::type_id::string}, {vm_context.gc.add( new cuttle::vm::string_t)}}, \
            {{cuttle::vm::type_id::integral}, {vm_context.gc.add( new cuttle::vm::integral_t)}}, \
            {{cuttle::vm::type_id::integral}, {vm_context.gc.add( new cuttle::vm::integral_t)}}, \
            {{cuttle::vm::type_id::integral}, {vm_context.gc.add( new cuttle::vm::integral_t)}} \
        } \
    ) \
    }}

namespace cuttle {
    namespace lang {
        const char *PARSER_CONTEXT_VAR_NAME = "__cuttle_parser_context";
        const char *PARSER_CONTEXT_CONFIG_ARRAY_VAR_NAME = "__cuttle_parser_context_config_array";
        const vm::type_t PARSER_CONTEXT_CONFIG_TYPE = {vm::type_id::array, {
                {vm::type_id::string},
                {vm::type_id::integral}
        }};

        enum context_configuration_indexes {
            func_name_ind,
            type_ind,
            args_number_ind,
            priority_after_ind
        };

        void register_lang_parser_cutvm_functions(vm::context_t &context);
    }
}