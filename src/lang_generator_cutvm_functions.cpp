#include <algorithm>
#include "generator_presenters_map_methods.hpp"
#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"
#include "lang_generator_cutvm_functions.hpp"
#include "generator_config.hpp"
#include "generator_presenters_methods.hpp"

using namespace cuttle::vm;

int lang_generator_cutvm_name_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    array_t *config_array = get(context, GENERATOR_CONFIG_ARRAY_VAR_NAME,
                                cuttle::lang::GENERATOR_CONFIG_TYPE).data.array;

    value_t func_id = {args[0].type, {context.gc.add(new string_t{*args[0].data.string})}};
    config_array->at(cuttle::lang::generator_config_configuration_indexes::func_name_ind) = func_id;

    ret = args[0];
    return 0;
}

int lang_generator_cutvm_before_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    array_t *config_array = get(context, GENERATOR_CONFIG_ARRAY_VAR_NAME,
                                cuttle::lang::GENERATOR_CONFIG_TYPE).data.array;

    value_t before = {args[0].type, {context.gc.add(new string_t{*args[0].data.string})}};
    config_array->at(cuttle::lang::generator_config_configuration_indexes::before_ind) = before;

    ret = args[0];
    return 0;
}

int lang_generator_cutvm_after_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    array_t *config_array = get(context, GENERATOR_CONFIG_ARRAY_VAR_NAME,
                                cuttle::lang::GENERATOR_CONFIG_TYPE).data.array;

    value_t after = {args[0].type, {context.gc.add(new string_t{*args[0].data.string})}};
    config_array->at(cuttle::lang::generator_config_configuration_indexes::after_ind) = after;

    ret = args[0];
    return 0;
}

int
lang_generator_cutvm_hide_function_name_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    array_t *config_array = get(context, GENERATOR_CONFIG_ARRAY_VAR_NAME,
                                cuttle::lang::GENERATOR_CONFIG_TYPE).data.array;

    value_t func_id = {args[0].type, {context.gc.add(new string_t{*args[0].data.string})}};
    config_array->at(cuttle::lang::generator_config_configuration_indexes::hide_function_name_ind) = args[0];
    return 0;
}

std::string lang_generator_presenter_before_func(int argi, bool is_func, cuttle::generator_presenter_params_t &params) {
    if (is_func) return params.before_func;
    if (params.before.count(argi) == 0) {
        if (params.before.count(0) == 0) {
            return "";
        } else {
            return params.before[0];
        }
    }
    return params.before[argi];
}

std::string lang_generator_presenter_after_func(int argi, bool is_func, cuttle::generator_presenter_params_t &params) {
    if (is_func) return params.after_func;
    if (params.after.count(argi) == 0) {
        if (params.after.count(0) == 0) {
            return "";
        } else {
            return params.after[0];
        }
    }
    return params.before[argi];
}

bool lang_generator_presenter_skip_func(int argi, bool is_func, cuttle::generator_presenter_params_t &params) {
    if (is_func) return params.hide_function_name;
    if (params.skip.count(argi) == 0) {
        if (params.skip.count(0) == 0) {
            return false;
        } else {
            return params.skip[0];
        }
    }
    return params.skip[argi];
}

int lang_generator_cutvm_append_to_generator_config_func(context_t &context, const std::vector<value_t> &args,
                                                              value_t &ret) {
    array_t *config_array = get(context, GENERATOR_CONFIG_ARRAY_VAR_NAME,
                                cuttle::lang::GENERATOR_CONFIG_TYPE).data.array;
    auto *generator_config = (cuttle::generator_config_t *) get(context, GENERATOR_CONFIG_VAR_NAME,
                                                                {type_id::object}).data.object;

    auto func_name = *config_array->at(cuttle::lang::generator_config_configuration_indexes::func_name_ind).data.string;
    auto before = *config_array->at(cuttle::lang::generator_config_configuration_indexes::before_ind).data.string;
    auto after = *config_array->at(cuttle::lang::generator_config_configuration_indexes::after_ind).data.string;
    bool hide_function_name = *config_array->at(
            cuttle::lang::generator_config_configuration_indexes::hide_function_name_ind).data.boolean;

    cuttle::generator_config_t &generator_config_ref = *generator_config;
    generator_config_ref.presenters_params[func_name] = {hide_function_name, before, after};
    cuttle::add(generator_config_ref.presenters_map, func_name,
                lang_generator_presenter_before_func,
                lang_generator_presenter_after_func,
                lang_generator_presenter_skip_func);

    ret = value_t{{type_id::string},
                  {context.gc.add(new string_t{func_name})}};
    return 0;
}

void cuttle::lang::register_lang_generator_cutvm_functions(vm::context_t &context) {
    value_t name = {{type_id::function, {{type_id::string}}}};
    name.data.function = lang_generator_cutvm_name_func;
    add(context, "name", name);

    value_t before = {{type_id::function, {{type_id::string}}}};
    before.data.function = lang_generator_cutvm_before_func;
    add(context, "before", before);

    value_t after = {{type_id::function, {{type_id::string}}}};
    after.data.function = lang_generator_cutvm_after_func;
    add(context, "after", after);

    value_t hide_function_name = {{type_id::function, {{type_id::boolean}}}};
    hide_function_name.data.function = lang_generator_cutvm_hide_function_name_func;
    add(context, "hide_function_name", hide_function_name);

    value_t append_to_generator_config = {{type_id::function, {}}};
    append_to_generator_config.data.function = lang_generator_cutvm_append_to_generator_config_func;
    add(context, "append_to_generator_config", append_to_generator_config);
}