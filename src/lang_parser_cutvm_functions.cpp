#include <algorithm>
#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"
#include "lang_parser_cutvm_functions.hpp"
#include "context_methods.hpp"

using namespace cuttle::vm;

int lang_parser_cutvm_name_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    array_t *config_array = get(context, PARSER_CONTEXT_ARRAY_VAR_NAME,
                                cuttle::lang::PARSER_CONTEXT_CONFIG_TYPE).data.array;

    value_t func_id = {args[0].type, {context.gc.add(new string_t{*args[0].data.string})}};
    config_array->at(cuttle::lang::context_configuration_indexes::func_name_ind) = func_id;

    ret = args[0];
    return 0;
}

int lang_parser_cutvm_type_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    array_t *config_array = get(context, PARSER_CONTEXT_ARRAY_VAR_NAME,
                                cuttle::lang::PARSER_CONTEXT_CONFIG_TYPE).data.array;

    value_t func_id = {args[0].type, {context.gc.add(new integral_t{*args[0].data.integral})}};
    config_array->at(cuttle::lang::context_configuration_indexes::type_ind) = func_id;

    ret = args[0];
    return 0;
}

int lang_parser_cutvm_prefix_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(
                   new integral_t(cuttle::function_type::prefix)
           )}};
    return 0;
}

int lang_parser_cutvm_infix_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(
                   new integral_t(cuttle::function_type::infix)
           )}};
    return 0;
}

int lang_parser_cutvm_postfix_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(
                   new integral_t(cuttle::function_type::postfix)
           )}};
    return 0;
}

int lang_parser_cutvm_args_number_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    array_t *config_array = get(context, PARSER_CONTEXT_ARRAY_VAR_NAME,
                                cuttle::lang::PARSER_CONTEXT_CONFIG_TYPE).data.array;

    value_t func_id = {args[0].type, {context.gc.add(new integral_t{*args[0].data.integral})}};
    config_array->at(cuttle::lang::context_configuration_indexes::args_number_ind) = func_id;

    ret = args[0];
    return 0;
}


int lang_parser_cutvm_priority_after_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    array_t *config_array = get(context, PARSER_CONTEXT_ARRAY_VAR_NAME,
                                cuttle::lang::PARSER_CONTEXT_CONFIG_TYPE).data.array;

    value_t func_id = {args[0].type, {context.gc.add(new integral_t{*args[0].data.integral})}};
    config_array->at(cuttle::lang::context_configuration_indexes::priority_after_ind) = func_id;

    ret = args[0];
    return 0;
}

int lang_parser_cutvm_start_func_id_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(
                   new integral_t(cuttle::FUNCTION_ID_UNKNOWN)
           )}};
    return 0;
}

int lang_parser_cutvm_func_id_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    auto *parser_context = (cuttle::context_t *) get(context, PARSER_CONTEXT_VAR_NAME,
                                                     {type_id::object}).data.object;

    ret = {{type_id::integral},
           {context.gc.add_r(
                   new integral_t(parser_context->funcname_to_id[*args[0].data.string])
           )}};
    return 0;
}

int lang_parser_cutvm_append_to_context_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    array_t *config_array = get(context, PARSER_CONTEXT_ARRAY_VAR_NAME,
                                cuttle::lang::PARSER_CONTEXT_CONFIG_TYPE).data.array;
    auto *parser_context = (cuttle::context_t *) get(context, PARSER_CONTEXT_VAR_NAME,
                                                     {type_id::object}).data.object;

    auto func_name = *config_array->at(cuttle::lang::context_configuration_indexes::func_name_ind).data.string;
    auto func_type = (cuttle::function_type) *config_array->at(
            cuttle::lang::context_configuration_indexes::type_ind).data.integral;
    auto args_number = (unsigned int) *config_array->at(
            cuttle::lang::context_configuration_indexes::args_number_ind).data.integral;
    auto priority_after = (cuttle::function_id_t) *config_array->at(
            cuttle::lang::context_configuration_indexes::priority_after_ind).data.integral;

    cuttle::context_t &parser_context_ref = *parser_context;
    cuttle::add(parser_context_ref, func_name, cuttle::function_t{func_type, args_number}, priority_after);

    ret = value_t{{type_id::integral}, {context.gc.add(new integral_t {0})}};
    return 0;
}

void cuttle::lang::register_lang_parser_cutvm_functions(vm::context_t &context) {
    value_t name = {{type_id::function, {{type_id::string}}}};
    name.data.function = lang_parser_cutvm_name_func;
    add(context, "name", name);

    value_t type = {{type_id::function, {{type_id::integral}}}};
    type.data.function = lang_parser_cutvm_type_func;
    add(context, "type", type);

    value_t prefix = {{type_id::function, {}}};
    prefix.data.function = lang_parser_cutvm_prefix_func;
    add(context, "prefix", prefix);

    value_t infix = {{type_id::function, {}}};
    infix.data.function = lang_parser_cutvm_infix_func;
    add(context, "infix", infix);

    value_t postfix = {{type_id::function, {}}};
    postfix.data.function = lang_parser_cutvm_postfix_func;
    add(context, "postfix", postfix);

    value_t args_number = {{type_id::function, {{type_id::integral}}}};
    args_number.data.function = lang_parser_cutvm_args_number_func;
    add(context, "args_number", args_number);

    value_t priority_after = {{type_id::function, {{type_id::integral}}}};
    priority_after.data.function = lang_parser_cutvm_priority_after_func;
    add(context, "priority_after", priority_after);

    value_t start_func_id = {{type_id::function, {}}};
    start_func_id.data.function = lang_parser_cutvm_start_func_id_func;
    add(context, "start_func_id", start_func_id);

    value_t func_id = {{type_id::function, {{type_id::string}}}};
    func_id.data.function = lang_parser_cutvm_func_id_func;
    add(context, "func_id", func_id);

    value_t append_to_context = {{type_id::function, {}}};
    append_to_context.data.function = lang_parser_cutvm_append_to_context_func;
    add(context, "append_to_context", append_to_context);
}