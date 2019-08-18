#include <algorithm>

#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"
#include "context_methods.hpp"
#include "lang_parser_cutvm_functions.hpp"

using namespace cuttle::vm;

int lang_parser_cutvm_root_func(context_t &context, const std::vector<value_t> &, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(new integral_t(cuttle::FUNCTION_ID_UNKNOWN)
           )}};
    return 0;
}

int lang_parser_cutvm_prefix_func(context_t &context, const std::vector<value_t> &, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(new integral_t(cuttle::function_type::prefix))}};
    return 0;
}

int lang_parser_cutvm_infix_func(context_t &context, const std::vector<value_t> &, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(new integral_t(cuttle::function_type::infix))}};
    return 0;
}

int lang_parser_cutvm_postfix_func(context_t &context, const std::vector<value_t> &, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(new integral_t(cuttle::function_type::postfix))}};
    return 0;
}

int lang_parser_cutvm_postprefix_func(context_t &context, const std::vector<value_t> &, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(new integral_t(cuttle::function_type::postprefix))}};
    return 0;
}

int lang_parser_cutvm_postinfix_func(context_t &context, const std::vector<value_t> &, value_t &ret) {
    ret = {{type_id::integral},
           {context.gc.add_r(new integral_t(cuttle::function_type::postinfix))}};
    return 0;
}

int lang_parser_cutvm_before_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    auto *parser_context = (cuttle::context_t *) get(context, PARSER_CONTEXT_VAR_NAME,
                                                     {type_id::object}).data.object;

    ret = {{type_id::integral},
           {context.gc.add_r(
                   new integral_t(parser_context->funcname_to_id[*args[0].data.string])
           )}};
    return 0;
}

int lang_parser_cutvm_add_parser_config_rule_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    using namespace cuttle;

    auto *parser_context = (cuttle::context_t *) get(context, PARSER_CONTEXT_VAR_NAME,
                                                     {type_id::object}).data.object;

    auto func_name = args[0];
    auto func_type = (function_type) *args[1].data.integral;
    auto args_number = (unsigned int) *args[2].data.integral;
    auto priority_after = (cuttle::function_id_t) *args[3].data.integral;

    cuttle::context_t &parser_context_ref = *parser_context;
    if (func_name.type.id == type_id::string) {
        cuttle::add(parser_context_ref, *func_name.data.string, cuttle::function_t{func_type, args_number}, priority_after);
    } else if (func_name.type.id == type_id::array) {
        cuttle::add(parser_context_ref, *func_name.data.array->at(0).data.string, cuttle::function_t{func_type, args_number}, priority_after, *func_name.data.array->at(1).data.string);
    }

    ret = value_t{{type_id::integral}, {context.gc.add(new integral_t {0})}};
    return 0;
}

void cuttle::lang::register_lang_parser_cutvm_functions(vm::context_t &context) {
    value_t root = {{type_id::function, {}}};
    root.data.function = lang_parser_cutvm_root_func;
    add(context, "root", root);

    value_t prefix = {{type_id::function, {}}};
    prefix.data.function = lang_parser_cutvm_prefix_func;
    add(context, "prefix", prefix);

    value_t infix = {{type_id::function, {}}};
    infix.data.function = lang_parser_cutvm_infix_func;
    add(context, "infix", infix);

    value_t postfix = {{type_id::function, {}}};
    postfix.data.function = lang_parser_cutvm_postfix_func;
    add(context, "postfix", postfix);

    value_t postprefix = {{type_id::function, {}}};
    postprefix.data.function = lang_parser_cutvm_postprefix_func;
    add(context, "postprefix", postprefix);

    value_t postinfix = {{type_id::function, {}}};
    postinfix.data.function = lang_parser_cutvm_postinfix_func;
    add(context, "postinfix", postinfix);

    value_t before = {{type_id::function, {{type_id::string}}}};
    before.data.function = lang_parser_cutvm_before_func;
    add(context, "before", before);

    value_t add_parser_config_rule = {{type_id::function, {
        {type_id::string},
        {type_id::integral},
        {type_id::integral},
        {type_id::integral}
    }}};
    add_parser_config_rule.data.function = lang_parser_cutvm_add_parser_config_rule_func;
    add(context, "add_parser_config_rule", add_parser_config_rule);

    value_t add_parser_config_rule_array = {{type_id::function, {
         {type_id::array, {{type_id::string}}},
         {type_id::integral},
         {type_id::integral},
         {type_id::integral}
    }}};
    add_parser_config_rule_array.data.function = lang_parser_cutvm_add_parser_config_rule_func;
    add(context, "add_parser_config_rule", add_parser_config_rule_array);

    value_t association = {{type_id::function, {{type_id::string}, {type_id::string}}}};
    association.data.function = get(context, "array", {type_id::any}).data.function;
    add(context, "->", association);
}