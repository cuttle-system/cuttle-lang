#include "value_methods.hpp"
#include "lang_parser_cutvm_translator.hpp"
#include "translator_methods.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "unsupported_cutvm_type_error.hpp"
#include "cutvm_type_utils.hpp"

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
                    dictionary_funcs::parameter(state, "_type")
            })
    }));

    arg_b_id = df::function_name(state, "b");
    type_id = df::function_name(state,"i");
    tree_src_element_t args_number_id = with_args_number
                                        ? dictionary_funcs::parameter(state, "_args_number")
                                        : dictionary_funcs::number(state, "0");

    args_indexes.push_back(df::function(state, arg_b_id, {
            df::function(state, type_id, {
                    args_number_id
            })
    }));

    arg_b_id = df::function_name(state, "b");
    type_id = df::function_name(state,"s");
    tree_src_element_t before_function_id = root_function
            ? dictionary_funcs::string(state, "")
            : dictionary_funcs::parameter(state, "_before_function");

    args_indexes.push_back(df::function(state, arg_b_id, {
            df::function(state, type_id, {
                    before_function_id
            })
    }));

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

tree_src_element_t lang_parser_cutvm_rule_entry_with_specifying_args_and_root_function(translate_state_t &state) {
    return lang_parser_cutvm_rule_entry(state, true, true);
}

tree_src_element_t lang_parser_cutvm_rule_entry_with_root_function(translate_state_t &state) {
    return lang_parser_cutvm_rule_entry(state, false, true);
}

void lang::get_lang_parser_cutvm_translator(translator_t &translator) {
    translator = {{"cutc-parser", 2}, {"cutvm", 1}, {}};
    initialize(translator.dictionary);

    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {3}, {}, {0}},
                                           {}},
        tokens_t{
                token_t{token_type::macro_pf, "_type"},
                token_t{token_type::macro_pvs, "_name"},
                token_t{token_type::atom, "before"},
                token_t{token_type::macro_pvs, "_before_function"},
        },
        lang_parser_cutvm_rule_entry_default);

    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {}, {0}},
                                           {}},
        tokens_t{
                token_t{token_type::macro_pf, "_type"},
                token_t{token_type::macro_p, "_name"},
                token_t{token_type::atom, "root"},
        },
        lang_parser_cutvm_rule_entry_with_root_function);

    add(translator.dictionary, call_tree_t{{{1, 2, 4}, {}, {3}, {}, {5}, {}, {0}},
                                           {}},
        tokens_t{
                token_t{token_type::macro_pf, "_type"},
                token_t{token_type::macro_pvs, "_name"},
                token_t{token_type::atom, ".."},
                token_t{token_type::macro_pvn, "_args_number"},
                token_t{token_type::atom, "before"},
                token_t{token_type::macro_pvs, "_before_function"},
        },
        lang_parser_cutvm_rule_entry_with_specifying_args);

    add(translator.dictionary, call_tree_t{{{1, 2, 4}, {}, {3}, {}, {}, {0}},
                                           {}},
        tokens_t{
                token_t{token_type::macro_pf, "_type"},
                token_t{token_type::macro_pvs, "_name"},
                token_t{token_type::atom, ".."},
                token_t{token_type::macro_pvn, "_args_number"},
                token_t{token_type::atom, "root"},
        },
        lang_parser_cutvm_rule_entry_with_specifying_args_and_root_function);
}