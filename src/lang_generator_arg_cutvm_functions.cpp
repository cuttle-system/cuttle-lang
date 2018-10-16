#include <algorithm>
#include "generator_presenters_map_methods.hpp"
#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"
#include "lang_generator_arg_cutvm_functions.hpp"
#include "generator_config.hpp"
#include "generator_presenters_methods.hpp"
#include "generator_presenters.hpp"

using namespace cuttle::vm;

int lang_generator_arg_cutvm_before_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    auto *presenter_params = (cuttle::generator_presenter_params_t *) get(context, PRESENTER_PARAMS_VAR_NAME,
                                                                          {type_id::object}).data.object;

    auto presenter_params_argi = *get(context, PRESENTER_PARAMS_ARGI_VAR_NAME,
                                  {type_id::object}).data.integral;

    cuttle::generator_presenter_params_t &presenter_params_ref = *presenter_params;
    presenter_params_ref.before[presenter_params_argi] = *args[0].data.string;

    ret = args[0];
    return 0;
}

int lang_generator_arg_cutvm_after_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    auto *presenter_params = (cuttle::generator_presenter_params_t *) get(context, PRESENTER_PARAMS_VAR_NAME,
                                                                          {type_id::object}).data.object;

    auto presenter_params_argi = *get(context, PRESENTER_PARAMS_ARGI_VAR_NAME,
                                      {type_id::object}).data.integral;

    cuttle::generator_presenter_params_t &presenter_params_ref = *presenter_params;
    presenter_params_ref.after[presenter_params_argi] = *args[0].data.string;

    ret = args[0];
    return 0;
}

int lang_generator_arg_cutvm_skip_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    auto *presenter_params = (cuttle::generator_presenter_params_t *) get(context, PRESENTER_PARAMS_VAR_NAME,
                                                                          {type_id::object}).data.object;

    auto presenter_params_argi = *get(context, PRESENTER_PARAMS_ARGI_VAR_NAME,
                                      {type_id::object}).data.integral;

    cuttle::generator_presenter_params_t &presenter_params_ref = *presenter_params;
    presenter_params_ref.skip[presenter_params_argi] = *args[0].data.boolean;

    ret = args[0];
    return 0;
}

void cuttle::lang::register_lang_generator_arg_cutvm_functions(vm::context_t &context) {
    value_t before = {{type_id::function, {{type_id::string}}}};
    before.data.function = lang_generator_arg_cutvm_before_func;
    add(context, "before", before);

    value_t after = {{type_id::function, {{type_id::string}}}};
    after.data.function = lang_generator_arg_cutvm_after_func;
    add(context, "after", after);

    value_t skip = {{type_id::function, {{type_id::boolean}}}};
    skip.data.function = lang_generator_arg_cutvm_skip_func;
    add(context, "skip", skip);
}