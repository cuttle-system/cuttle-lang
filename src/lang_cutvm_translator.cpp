#include "value_methods.hpp"
#include "lang_cutvm_translator.hpp"
#include "translator_methods.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "unsupported_cutvm_type_error.hpp"
#include "cutvm_type_utils.hpp"

using namespace cuttle;

tree_src_element_t lang::cutvm_function_call(translate_state_t &state,
        tree_src_element_t function_name,
        const std::vector<tree_src_element_t> &initial_args_indexes
) {
    namespace df = cuttle::dictionary_funcs;

    std::vector<tree_src_element_t> args_indexes;

    unsigned int call_id;
    if (state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }

    for (auto arg_index : initial_args_indexes) {
        tree_src_element_t arg_b_id;
        translate_state_t child_state = state;
        child_state.index = arg_index;
        arg_b_id = translate_function_call(child_state);
        state.index_reference[arg_index] = arg_b_id;
        args_indexes.push_back(arg_b_id);
    }

    auto c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, std::to_string(args_indexes.size())),
            df::number(state, std::to_string(args_indexes.size())),
            df::function(state, function_name, {})
    }));

    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t lang::cutvm_push_value_to_stack(translate_state_t &state) {
    namespace df = cuttle::dictionary_funcs;

    auto token_value_type = value_from_token_type(state.tokens[state.index].type);
    tree_src_element_t arg_b_id = df::function_name(state, "b");
    auto type_id = df::function_name(state, cutvm_type_from_value_type(token_value_type));
    return df::function(state, arg_b_id, {
            df::function(state, type_id, {
                    df::value(state, state.tokens[state.index].value, token_value_type)
            })
    });
}

void get_lang_cutvm_translator_base(translator_t &translator) {
//    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {}, {0}}},
//        tokens_t{token_t{token_type::atom, "+"},
//                 token_t{token_type::macro_p, "_a"},
//                 token_t{token_type::macro_p, "_b"}},
//        [](translate_state_t &state) {
//            namespace df = dictionary_funcs;
//            auto function_index = state.index;
//            return lang::cutvm_function_call(state,
//                                             df::function_name(state, state.tokens[function_index].value), state.tree.src[function_index]);
//        });
//    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {}, {0}}},
//        tokens_t{token_t{token_type::atom, "-"},
//                 token_t{token_type::macro_p, "_a"},
//                 token_t{token_type::macro_p, "_b"}},
//        [](translate_state_t &state) {
//            namespace df = dictionary_funcs;
//            auto function_index = state.index;
//            return lang::cutvm_function_call(state,
//                                             df::function_name(state, state.tokens[function_index].value), state.tree.src[function_index]);
//        });
//    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {}, {0}}},
//        tokens_t{token_t{token_type::atom, "string"},
//                 token_t{token_type::macro_p, "_a"}},
//        [](translate_state_t &state) {
//            namespace df = dictionary_funcs;
//            auto function_index = state.index;
//            return lang::cutvm_function_call(state,
//                                             df::function_name(state, state.tokens[function_index].value), state.tree.src[function_index]);
//        });
    add(translator.dictionary, call_tree_t{{{}, {0}}},
        tokens_t{token_t{token_type::macro_pva, "_func"}},
        [](translate_state_t &state) {
            namespace df = dictionary_funcs;
            auto function_index = state.index;
            return lang::cutvm_function_call(state,
                                             df::function_name(state, state.tokens[function_index].value), state.tree.src[function_index]);
        });

    add(translator.dictionary, call_tree_t{{{}, {0}}},
        tokens_t{token_t{token_type::macro_pvs, "_string"}},
        lang::cutvm_push_value_to_stack);

    add(translator.dictionary, call_tree_t{{{}, {0}}},
        tokens_t{token_t{token_type::macro_pvn, "_number"}},
        lang::cutvm_push_value_to_stack);
}


void lang::get_lang_cutvm_translator(translator_t &translator) {
    translator = {{TRANSLATOR_ANY_NAME, TRANSLATOR_ANY_VERSION}, {"cutvm", 1}, {}};
    initialize(translator.dictionary);

    get_lang_cutvm_translator_base(translator);
}