#include "value_methods.hpp"
#include "lang_parser_cutvm_translator.hpp"
#include "translator_methods.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "unsupported_cutvm_type_error.hpp"
#include "cutvm_type_utils.hpp"
#include "cutvm_translator.hpp"
#include "lang_cutvm_translator.hpp"

using namespace cuttle;

tree_src_element_t lang_parser_cutvm_rule_entry(translate_state_t &state, bool with_args_number = false, bool root_function = false) {
    namespace df = cuttle::dictionary_funcs;

    std::vector<tree_src_element_t> args_indexes;

    unsigned int call_id;
    if (state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }

    tree_src_element_t arg_b_id, c_id, type_id;

    args_indexes.push_back(dictionary_funcs::parameter(state, "_name"));

    c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            dictionary_funcs::number(state, "0"),
            dictionary_funcs::number(state, "0"),
            dictionary_funcs::function_name(state, state.tokens[state.index].value)
    }));

    if (with_args_number) {
        args_indexes.push_back(dictionary_funcs::parameter(state, "_args_number"));
    } else {
        arg_b_id = df::function_name(state, "b");
        type_id = df::function_name(state,"i");

        args_indexes.push_back(df::function(state, arg_b_id, {
                df::function(state, type_id, {
                        dictionary_funcs::number(state, "0")
                })
        }));
    }

    args_indexes.push_back(dictionary_funcs::parameter(state, "_priority"));

    c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "4"),
            df::number(state, "4"),
            df::function(state, df::function_name(state, "add_parser_config_rule"), {})
    }));

    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t lang_parser_cutvm_rule_entry_default(translate_state_t &state) {
    return lang_parser_cutvm_rule_entry(state);
}

tree_src_element_t lang_parser_cutvm_rule_entry_with_specifying_args(translate_state_t &state) {
    return lang_parser_cutvm_rule_entry(state, true);
}

void lang_parser_cutvm_translator_add_function_type(dictionary_t &dictionary, const std::string &type_name) {
    add(dictionary, call_tree_t{{{1, 2}, {}, {}, {0}},
                                           {}},
        tokens_t{
                token_t{token_type::atom, type_name},
                token_t{token_type::macro_p, "_name"},
                token_t{token_type::macro_p, "_priority"},
        },
        lang_parser_cutvm_rule_entry_default);

    add(dictionary, call_tree_t{{{1, 2, 4}, {}, {3}, {}, {}, {0}},
                                           {}},
        tokens_t{
                token_t{token_type::atom, type_name},
                token_t{token_type::macro_p, "_name"},
                token_t{token_type::atom, ".."},
                token_t{token_type::macro_p, "_args_number"},
                token_t{token_type::macro_p, "_priority"},
        },
        lang_parser_cutvm_rule_entry_with_specifying_args);
}

void lang::get_lang_parser_cutvm_translator(translator_t &translator) {
    get_lang_cutvm_translator(translator);
    translator.from = {"cutc-parser", 2};
    translator.to = {"cutvm", 1};


    lang_parser_cutvm_translator_add_function_type(translator.dictionary, "prefix");
    lang_parser_cutvm_translator_add_function_type(translator.dictionary, "infix");
    lang_parser_cutvm_translator_add_function_type(translator.dictionary, "postfix");
    lang_parser_cutvm_translator_add_function_type(translator.dictionary, "postprefix");
    lang_parser_cutvm_translator_add_function_type(translator.dictionary, "postinfix");

}