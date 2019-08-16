#include "value_methods.hpp"
#include "lang_generator_cutvm_translator.hpp"
#include "translator_methods.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "unsupported_cutvm_type_error.hpp"
#include "cutvm_type_utils.hpp"

using namespace cuttle;

tree_src_element_t lang_generator_cutvm_rule_entry(translate_state_t &state, bool hide_function_name = false) {
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

    arg_b_id = df::function_name(state, "b");
    type_id = df::function_name(state,"s");
    args_indexes.push_back(df::function(state, arg_b_id, {
            df::function(state, type_id, {
                    dictionary_funcs::parameter(state, "_name")
            })
    }));

    arg_b_id = df::function_name(state, "b");
    type_id = df::function_name(state,"s");
    args_indexes.push_back(df::function(state, arg_b_id, {
            df::function(state, type_id, {
                    dictionary_funcs::parameter(state, "_before")
            })
    }));

    arg_b_id = df::function_name(state, "b");
    type_id = df::function_name(state,"s");
    args_indexes.push_back(df::function(state, arg_b_id, {
            df::function(state, type_id, {
                    dictionary_funcs::parameter(state, "_after")
            })
    }));

    arg_b_id = df::function_name(state, "b");
    type_id = df::function_name(state,"b");
    args_indexes.push_back(df::function(state, arg_b_id, {
            df::function(state, type_id, {
                    df::string(state, hide_function_name ? "true" : "false")
            })
    }));

    c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "4"),
            df::number(state, "4"),
            df::function(state, df::function_name(state, "add_generator_config_rule"), {})
    }));

    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t lang_generator_cutvm_rule_entry_default(translate_state_t &state) {
    return lang_generator_cutvm_rule_entry(state);
}

tree_src_element_t lang_generator_cutvm_rule_entry_hide_function_name(translate_state_t &state) {
    return lang_generator_cutvm_rule_entry(state, true);
}

void lang::get_lang_generator_cutvm_translator(translator_t &translator) {
    translator = {{"cutc-generator", 1}, {"cutvm", 1}, {}};
    initialize(translator.dictionary);

    add(translator.dictionary, call_tree_t{{{}, {0, 3}, {}, {2, 4}, {}, {1}},
                                           {}},
        tokens_t{
                token_t{token_type::macro_p, "_before"},
                token_t{token_type::atom, "->"},
                token_t{token_type::macro_p, "_name"},
                token_t{token_type::atom, "<-"},
                token_t{token_type::macro_p, "_after"},
        },
        lang_generator_cutvm_rule_entry_default);


    add(translator.dictionary, call_tree_t{{{}, {0, 4}, {3}, {}, {2, 5}, {}, {1}}, {}},
        tokens_t{
                token_t{token_type::macro_p, "_before"},
                token_t{token_type::atom, "->"},
                token_t{token_type::atom, "_"},
                token_t{token_type::macro_p, "_name"},
                token_t{token_type::atom, "<-"},
                token_t{token_type::macro_p, "_after"},
        },
        lang_generator_cutvm_rule_entry_hide_function_name);
}