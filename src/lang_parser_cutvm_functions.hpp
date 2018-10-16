#pragma once

#include "vm_context.hpp"
#include "vm_value.hpp"
#include "function.hpp"

#define PARSER_CONTEXT_CONFIG_ARRAY_DEFAULT_VALUES cuttle::vm::value_t{cuttle::lang::PARSER_CONTEXT_CONFIG_TYPE, \
    { \
    vm_context.gc.add( \
        new cuttle::vm::array_t{ \
            {{cuttle::vm::type_id::string}, {vm_context.gc.add( new cuttle::vm::string_t(""))}}, \
            {{cuttle::vm::type_id::integral}, {vm_context.gc.add( new cuttle::vm::integral_t(cuttle::function_type::prefix))}}, \
            {{cuttle::vm::type_id::integral}, {vm_context.gc.add( new cuttle::vm::integral_t(1))}}, \
            {{cuttle::vm::type_id::integral}, {vm_context.gc.add( new cuttle::vm::integral_t(FUNCTION_ID_UNKNOWN))}} \
        } \
    ) \
    }}

#define PARSER_CONTEXT_VAR_NAME "__cuttle_parser_context"
#define PARSER_CONTEXT_ARRAY_VAR_NAME "__cuttle_parser_context_config_array"

namespace cuttle {
    namespace lang {
        const vm::type_t PARSER_CONTEXT_CONFIG_TYPE = {vm::type_id::array, {
                {vm::type_id::string},
                {vm::type_id::integral}
        }};

        enum context_configuration_indexes {
            func_name_ind,
            type_ind,
            args_number_ind,
            executes_before_ind
        };

        void register_lang_parser_cutvm_functions(vm::context_t &context);
    }
}