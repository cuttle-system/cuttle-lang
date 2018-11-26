#include <sstream>

#include "lang_output_translator.hpp"
#include "call_tree.hpp"
#include "dictionary_funcs.hpp"
#include "translator.hpp"
#include "cutvm_translator.hpp"
#include "translator_methods.hpp"
#include "value_methods.hpp"
#include "dictionary_methods.hpp"
#include "token_methods.hpp"

using namespace cuttle;
namespace df = dictionary_funcs;

tree_src_element_t output_translator_present_value(translate_state_t &state, tree_src_element_t index, bool function = false) {
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
    std::stringstream type_cutvm_value;
    type_cutvm_value << token.type;
    df::function(state, arg_b_type_id, {
            df::function(state, type_type_id, {
                    df::value(state, type_cutvm_value.str(), value_type::string)
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

tree_src_element_t output_translator_translate_if(translate_state_t &state) {
    std::vector<unsigned int> args_indexes;

    unsigned int call_id;
    if (state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }

    args_indexes.push_back(df::parameter(state, "_statement"));

    auto c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "1"),
            df::number(state, "1"),
            df::function(state, df::function_name(state, "not"), {})
    }));

    std::string endif_label = "endif" + std::to_string(state.custom_state_num["if"]++);

    c_id = df::function_name(state, "g");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, ">"),
            df::function(state, df::function_name(state, endif_label), {})
    }));

    args_indexes.push_back(df::parameter(state, "_block"));

    c_id = df::function_name(state, "l");
    args_indexes.push_back(df::function(state, c_id, {
            df::function(state, df::function_name(state, endif_label), {})
    }));

    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t output_translator_translate_if_else(translate_state_t &state) {
    std::vector<unsigned int> args_indexes;

    unsigned int call_id;
    if (state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }

    args_indexes.push_back(df::parameter(state, "_statement"));

    auto c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "1"),
            df::number(state, "1"),
            df::function(state, df::function_name(state, "not"), {})
    }));


    auto statement_id = std::to_string(state.custom_state_num["if"]++);
    std::string endif_label = "endif" + statement_id;
    std::string else_endif_label = "else_endif" + statement_id;

    c_id = df::function_name(state, "g");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, ">"),
            df::function(state, df::function_name(state, endif_label), {})
    }));

    args_indexes.push_back(df::parameter(state, "_block"));

    auto b_id = df::function_name(state, "b");
    auto s_id = df::function_name(state, "b");
    args_indexes.push_back(df::function(state, b_id, {
            df::function(state, s_id, {
                    df::string(state, "true")
            })
    }));

    c_id = df::function_name(state, "g");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, ">"),
            df::function(state, df::function_name(state, else_endif_label), {})
    }));

    c_id = df::function_name(state, "l");
    args_indexes.push_back(df::function(state, c_id, {
            df::function(state, df::function_name(state, endif_label), {})
    }));

    args_indexes.push_back(df::parameter(state, "_else_block"));

    c_id = df::function_name(state, "l");
    args_indexes.push_back(df::function(state, c_id, {
            df::function(state, df::function_name(state, else_endif_label), {})
    }));

    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t output_translator_translate_block(translate_state_t &state) {
    unsigned int call_id;
    if (state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }

    std::vector<unsigned int> args_indexes = df::copy(state, state.tree.src[state.index]);
    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t output_translator_translate_block_end(translate_state_t &state) {
    return CALL_TREE_SRC_NIL;
}

tree_src_element_t output_translator_translate_get(translate_state_t &state) {
    std::vector<unsigned int> args_indexes;

    unsigned int call_id;
    if (state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }


    args_indexes.push_back(df::parameter(state, "_name"));

    auto b_id = df::function_name(state, "b");
    auto s_id = df::function_name(state, "i");
    args_indexes.push_back(df::function(state, b_id, {
            df::function(state, s_id, {
                    df::number(state, "1")
            })
    }));

    auto c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "2"),
            df::number(state, "2"),
            df::function(state, df::function_name(state, "get_element"), {})
    }));

    c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "1"),
            df::number(state, "1"),
            df::function(state, df::function_name(state, "getvar"), {})
    }));

    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t output_translator_translate_eq(translate_state_t &state) {
    std::vector<unsigned int> args_indexes;

    unsigned int call_id;
    if (state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }

    args_indexes.push_back(df::parameter(state, "_left"));

    args_indexes.push_back(df::parameter(state, "_right"));

    auto b_id = df::function_name(state, "b");
    auto s_id = df::function_name(state, "i");
    args_indexes.push_back(df::function(state, b_id, {
            df::function(state, s_id, {
                    df::number(state, "1")
            })
    }));

    auto c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "2"),
            df::number(state, "2"),
            df::function(state, df::function_name(state, "get_element"), {})
    }));

    c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "2"),
            df::number(state, "2"),
            df::function(state, df::function_name(state, "=="), {})
    }));

    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t output_translator_translate_set(translate_state_t &state) {
    std::vector<unsigned int> args_indexes;

    unsigned int call_id;
    if (state.index_reference.find(state.index) != state.index_reference.end()) {
        call_id = state.index_reference[state.index];
        state.values[call_id] = {"call", value_type::func_name};
    } else {
        call_id = df::function_name(state, "call");
    }

    args_indexes.push_back(df::parameter(state, "_name"));

    auto b_id = df::function_name(state, "b");
    auto s_id = df::function_name(state, "i");
    args_indexes.push_back(df::function(state, b_id, {
            df::function(state, s_id, {
                    df::number(state, "1")
            })
    }));

    auto c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "2"),
            df::number(state, "2"),
            df::function(state, df::function_name(state, "get_element"), {})
    }));

    args_indexes.push_back(df::parameter(state, "_value"));

    b_id = df::function_name(state, "b");
    s_id = df::function_name(state, "i");
    args_indexes.push_back(df::function(state, b_id, {
            df::function(state, s_id, {
                    df::number(state, "1")
            })
    }));

    c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "2"),
            df::number(state, "2"),
            df::function(state, df::function_name(state, "get_element"), {})
    }));

    c_id = df::function_name(state, "c");
    args_indexes.push_back(df::function(state, c_id, {
            df::number(state, "2"),
            df::number(state, "2"),
            df::function(state, df::function_name(state, "setvar"), {})
    }));

    df::function(state, call_id, args_indexes);

    return call_id;
}

tree_src_element_t output_translator_translate(translate_state_t &state) {
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

    args_indexes.push_back(output_translator_present_value(state, state.index, true));

    for (auto arg_index : state.tree.src[state.index]) {
        value_type token_value_type;
        if (arg_index == CALL_TREE_SRC_NIL) {
            token_value_type = value_type::func_name;
        } else {
            token_value_type = value_from_token_type(state.tokens[arg_index].type);
        }
        tree_src_element_t arg_b_id;
        if (token_value_type != value_type::func_name || arg_index == CALL_TREE_SRC_NIL) {
            arg_b_id = output_translator_present_value(state, arg_index);
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

tree_src_element_t output_translator_translate_value(translate_state_t &state) {
    return output_translator_present_value(state, state.index);
}

void cuttle::lang::get_output_translator(translator_t &translator) {
    translator = {{TRANSLATOR_ANY_NAME, TRANSLATOR_ANY_VERSION},
                  {"cutvm-translator-output",       1},
                  {}};
    initialize(translator.dictionary);

    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {}, {0}}},
        tokens_t{token_t{token_type::macro_set, "0set"}, token_t{token_type::macro_p, "_name"}, token_t{token_type::macro_p, "_value"}},
        output_translator_translate_set);
    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {}, {0}}},
        tokens_t{token_t{token_type::macro_eq, "0eq"}, token_t{token_type::macro_p, "_left"}, token_t{token_type::macro_p, "_right"}},
        output_translator_translate_eq);
    add(translator.dictionary, call_tree_t{{{1}, {}, {0}}},
        tokens_t{token_t{token_type::macro_get, "0get"}, token_t{token_type::macro_p, "_name"}},
        output_translator_translate_get);

    add(translator.dictionary, call_tree_t{{{1}, {}, {0}}},
        tokens_t{token_t{token_type::macro_block_start, "0do"}, token_t{token_type::macro_block_end, "0end"}},
        output_translator_translate_block);
    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {}, {0}}},
        tokens_t{token_t{token_type::macro_block_start, "0do"}, token_t{token_type::macro_p, "_arg1"}, token_t{token_type::macro_block_end, "0end"}},
        output_translator_translate_block);
    add(translator.dictionary, call_tree_t{{{1, 2, 3}, {}, {}, {}, {0}}},
        tokens_t{token_t{token_type::macro_block_start, "0do"}, token_t{token_type::macro_p, "_arg1"}, token_t{token_type::macro_p, "_arg2"}, token_t{token_type::macro_block_end, "0end"}},
        output_translator_translate_block);

    add(translator.dictionary, call_tree_t{{{}, {0}}},
        tokens_t{token_t{token_type::macro_block_end, "0end"}},
        output_translator_translate_block_end);

    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {}, {0}}},
        tokens_t{token_t{token_type::macro_if, "0if"}, token_t{token_type::macro_p, "_statement"}, token_t{token_type::macro_p, "_block"}},
        output_translator_translate_if);
    add(translator.dictionary, call_tree_t{{{1, 2}, {}, {}, {0, 4}, {}, {3}}},
        tokens_t{token_t{token_type::macro_if, "0if"}, token_t{token_type::macro_p, "_statement"}, token_t{token_type::macro_p, "_block"},
                 token_t{token_type::macro_else, "0else"}, token_t{token_type::macro_p, "_else_block"}},
        output_translator_translate_if_else);
    add(translator.dictionary, call_tree_t{{{}, {0}}},
        tokens_t{token_t{token_type::macro_pf, "_func"}},
        output_translator_translate);
    add(translator.dictionary, call_tree_t{{{}, {0}}},
        tokens_t{token_t{token_type::macro_p, "_a"}},
        output_translator_translate_value);
}
