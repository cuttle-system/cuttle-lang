#pragma once

#include "vm_context.hpp"
#include "vm_value.hpp"
#include "generator_config.hpp"

#define GENERATOR_CONFIG_ARRAY_DEFAULT_VALUES cuttle::vm::value_t{cuttle::lang::GENERATOR_CONFIG_TYPE, \
    { \
    vm_context.gc.add( \
        new cuttle::vm::array_t{ \
            {{cuttle::vm::type_id::string}, {vm_context.gc.add( new cuttle::vm::string_t(""))}}, \
            {{cuttle::vm::type_id::boolean}, {vm_context.gc.add( new cuttle::vm::boolean_t(false))}}, \
            {{cuttle::vm::type_id::string}, {vm_context.gc.add( new cuttle::vm::string_t(""))}}, \
            {{cuttle::vm::type_id::string}, {vm_context.gc.add( new cuttle::vm::string_t(""))}} \
        } \
    ) \
    }}

#define GENERATOR_CONFIG_VAR_NAME "__cuttle_generator_config"
#define GENERATOR_CONFIG_ARRAY_VAR_NAME "__cuttle_generator_config_array"

namespace cuttle {
    namespace lang {
        const vm::type_t GENERATOR_CONFIG_TYPE = {vm::type_id::array, {
                {vm::type_id::string},
                {vm::type_id::integral},
                {vm::type_id::string},
                {vm::type_id::string}
        }};

        enum generator_config_configuration_indexes {
            func_name_ind,
            hide_function_name_ind,
            before_ind,
            after_ind
        };

        void register_lang_generator_cutvm_functions(vm::context_t &context);
    }
}