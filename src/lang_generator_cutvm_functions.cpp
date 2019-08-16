#include <algorithm>
#include "generator_presenters_map_methods.hpp"
#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"
#include "lang_generator_cutvm_functions.hpp"
#include "generator_config.hpp"
#include "generator_presenters_methods.hpp"

using namespace cuttle::vm;

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

int lang_generator_cutvm_add_generator_config_rule_func(context_t &context, const std::vector<value_t> &args,
                                                              value_t &ret) {
    auto func_name = *args[0].data.string;
    auto before = *args[1].data.string;
    auto after = *args[2].data.string;
    bool hide_function_name = *args[3].data.boolean;

    cuttle::generator_config_t generator_config;
    generator_config.presenters_params[func_name] = {hide_function_name, before, after, {}, {}, {}};
    cuttle::add(generator_config.presenters_map, func_name,
                lang_generator_presenter_before_func,
                lang_generator_presenter_after_func,
                lang_generator_presenter_skip_func);

    ret = value_t{{type_id::string},
                  {context.gc.add(new string_t{func_name})}};
    return 0;
}

void cuttle::lang::register_lang_generator_cutvm_functions(vm::context_t &context) {
    value_t add_generator_config_rule = {{type_id::function, {
        {type_id::string}, {type_id::string}, {type_id::string}, {type_id::boolean}}}};
    add_generator_config_rule.data.function = lang_generator_cutvm_add_generator_config_rule_func;
    add(context, "add_generator_config_rule", add_generator_config_rule);
}