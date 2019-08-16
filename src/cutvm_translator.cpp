#include "value_methods.hpp"
#include "cutvm_translator.hpp"
#include "translator_methods.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "unsupported_cutvm_type_error.hpp"
#include "cutvm_type_utils.hpp"
#include "token_methods.hpp"

using namespace cuttle;
namespace df = dictionary_funcs;

tree_src_element_t cutvm_translator_present_value(translate_state_t &state, tree_src_element_t index, bool function = false) {
    tree_src_element_t call_id;

    if (!function && state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }

    token_t token = (index == CALL_TREE_SRC_NIL) ? token_t{token_type::atom, CUTTLE_CUTVM_CALL_TREE_NIL} : state.tokens[index];

    auto arg_b_type_id = df::function_name(state, "b");
    auto type_type_id = df::function_name(state, "s");
    df::function(state, arg_b_type_id, {
            df::function(state, type_type_id, {
                    df::value(state, token_type_to_string(token.type), value_type::string)
            })
    });

    auto arg_b_value_id = df::function_name(state, "b");
    auto value_type_id = df::function_name(state, "s");
    df::function(state, arg_b_value_id, {
            df::function(state, value_type_id, {
                    df::value(state, token.value, value_type::string)
            })
    });

    auto c_id = df::function_name(state, "c");
    df::function(state, c_id, {
            df::number(state, "2"),
            df::number(state, "0"),
            df::function(state, df::function_name(state, "array"), {})
    });

    df::function(state, call_id, {arg_b_type_id, arg_b_value_id, c_id});

    return call_id;
}

tree_src_element_t cutvm_translator_translate(translate_state_t &state) {
    std::vector<unsigned int> args_indexes;

    unsigned int call_id;
    if (state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }

    auto b_id = df::function_name(state, "b");
    auto s_id = df::function_name(state, "s");
    args_indexes.push_back(df::function(state, b_id, {
            df::function(state, s_id, {
                    df::value(state, "f", value_type::string)
            })
    }));

    args_indexes.push_back(cutvm_translator_present_value(state, state.index, true));

    for (auto arg_index : state.tree.src[state.index]) {
        value_type token_value_type;
        if (arg_index == CALL_TREE_SRC_NIL) {
            token_value_type = value_type::func_name;
        } else {
            token_value_type = value_from_token_type(state.tokens[arg_index].type);
        }
        tree_src_element_t arg_b_id;
        if (token_value_type != value_type::func_name || arg_index == CALL_TREE_SRC_NIL) {
            arg_b_id = cutvm_translator_present_value(state, arg_index);
        } else {
            translate_state_t child_state = state;
            child_state.index = arg_index;
            arg_b_id = translate_function_call(child_state);
        }
        if (arg_index != CALL_TREE_SRC_NIL) {
            state.index_reference[arg_index] = arg_b_id;
        }
        args_indexes.push_back(arg_b_id);
    }

    auto c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, std::to_string(args_indexes.size())),
            df::number(state, "0"),
            df::function(state, df::function_name(state, "array"), {})
    }));

    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t cutvm_translator_translate_value(translate_state_t &state) {
    return cutvm_translator_present_value(state, state.index);
}

void lang::get_cutvm_translator(translator_t &translator) {
    translator = {{TRANSLATOR_ANY_NAME, TRANSLATOR_ANY_VERSION},
                  {"cutvm-cache",       1},
                  {}};
    initialize(translator.dictionary);

    add(translator.dictionary, call_tree_t{{{}, {0}}},
        tokens_t{token_t{token_type::macro_pva, "_func"}},
        cutvm_translator_translate);
    add(translator.dictionary, call_tree_t{{{}, {0}}},
        tokens_t{token_t{token_type::macro_p, "_a"}},
        cutvm_translator_translate_value);
}