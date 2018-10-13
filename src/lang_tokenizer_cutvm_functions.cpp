#include <algorithm>
#include "vm_context_methods.hpp"
#include "vm_value_methods.hpp"
#include "lang_tokenizer_cutvm_functions.hpp"
#include "context_methods.hpp"
#include "vm_context_methods.hpp"

using namespace cuttle::vm;

int lang_tokenizer_cutvm_formatted_string_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->formatted_string[*args[0].data.array->at(0).data.string].insert(*args[0].data.array->at(1).data.string);
    ret = args[0];
    return 0;
}

int lang_tokenizer_cutvm_normal_string_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->normal_string[*args[0].data.array->at(0).data.string].insert(*args[0].data.array->at(1).data.string);
    ret = args[0];
    return 0;
}

int lang_tokenizer_cutvm_separated_symbol_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->separated_symbols.insert(*args[0].data.string);
    ret = args[0];
    return 0;
}

int lang_tokenizer_cutvm_comments_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->comments[*args[0].data.array->at(0).data.string].insert(*args[0].data.array->at(1).data.string);
    ret = args[0];
    return 0;
}

int lang_tokenizer_cutvm_formatted_character_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->formatted_characters.insert({*args[0].data.array->at(0).data.string, *args[0].data.array->at(1).data.string});
    tokenizer_config->formatted_characters_output.insert({*args[0].data.array->at(1).data.string, *args[0].data.array->at(0).data.string});
    ret = args[0];
    return 0;
}

int lang_tokenizer_cutvm_macro_if_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->macro_if.insert(*args[0].data.array->at(0).data.string);
    ret = args[0];
    return 0;
}

int lang_tokenizer_cutvm_macro_ps_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->macro_ps[*args[0].data.array->at(0).data.string].insert(*args[0].data.array->at(1).data.string);
    ret = args[0];
    return 0;
}

int lang_tokenizer_cutvm_macro_pf_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->macro_pf[*args[0].data.array->at(0).data.string].insert(*args[0].data.array->at(1).data.string);
    ret = args[0];
    return 0;
}

int lang_tokenizer_cutvm_macro_p_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->macro_p[*args[0].data.array->at(0).data.string].insert(*args[0].data.array->at(1).data.string);
    ret = args[0];
    return 0;
}

int lang_tokenizer_cutvm_separate_digit_and_alpha_func(context_t &context, const std::vector<value_t> &args, value_t &ret) {
    cuttle::tokenizer_config_t *tokenizer_config = (cuttle::tokenizer_config_t *) get(context, TOKENIZER_CONFIG_VAR_NAME,
                                                                                      {type_id::object}).data.object;
    tokenizer_config->separate_digit_and_alpha = *args[0].data.boolean;
    ret = args[0];
    return 0;
}

void cuttle::lang::register_lang_tokenizer_cutvm_functions(vm::context_t &context) {
    value_t formatted_string = {{type_id::function, {{type_id::array, {{type_id::string}}}}}};
    formatted_string.data.function = lang_tokenizer_cutvm_formatted_string_func;
    add(context, "formatted_string", formatted_string);

    value_t normal_string = {{type_id::function, {{type_id::array, {{type_id::string}}}}}};
    normal_string.data.function = lang_tokenizer_cutvm_normal_string_func;
    add(context, "normal_string", normal_string);

    value_t separated_symbol = {{type_id::function, {{type_id::string}}}};
    separated_symbol.data.function = lang_tokenizer_cutvm_separated_symbol_func;
    add(context, "separated_symbol", separated_symbol);

    value_t comments = {{type_id::function, {{type_id::array, {{type_id::string}}}}}};
    comments.data.function = lang_tokenizer_cutvm_comments_func;
    add(context, "comments", comments);

    value_t formatted_character = {{type_id::function, {{type_id::array, {{type_id::string}}}}}};
    formatted_character.data.function = lang_tokenizer_cutvm_formatted_character_func;
    add(context, "formatted_character", formatted_character);

    value_t macro_if = {{type_id::function, {{type_id::string}}}};
    macro_if.data.function = lang_tokenizer_cutvm_macro_if_func;
    add(context, "macro_if", macro_if);

    value_t macro_ps = {{type_id::function, {{type_id::array, {{type_id::string}}}}}};
    macro_ps.data.function = lang_tokenizer_cutvm_macro_ps_func;
    add(context, "macro_ps", macro_ps);

    value_t macro_pf = {{type_id::function, {{type_id::array, {{type_id::string}}}}}};
    macro_pf.data.function = lang_tokenizer_cutvm_macro_pf_func;
    add(context, "macro_pf", macro_pf);

    value_t macro_p = {{type_id::function, {{type_id::array, {{type_id::string}}}}}};
    macro_p.data.function = lang_tokenizer_cutvm_macro_p_func;
    add(context, "macro_p", macro_p);

    value_t separate_digit_and_alpha = {{type_id::function, {{type_id::boolean}}}};
    separate_digit_and_alpha.data.function = lang_tokenizer_cutvm_separate_digit_and_alpha_func;
    add(context, "separate_digit_and_alpha", separate_digit_and_alpha);

    value_t association = {{type_id::function, {{type_id::string}, {type_id::string}}}};
    association.data.function = get(context, "array", {type_id::any}).data.function;
    add(context, "->", association);
}