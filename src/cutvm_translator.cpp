#include "value_methods.hpp"
#include "cutvm_translator.hpp"
#include "translator_methods.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "unsupported_cutvm_type_error.hpp"
#include "cutvm_type_utils.hpp"

using namespace cuttle;

void lang::get_cutvm_translator(translator_t &translator) {
    translator = {{TRANSLATOR_ANY_NAME, TRANSLATOR_ANY_VERSION}, {"cutvm", 1}, {}};
    initialize(translator.dictionary);

    add(translator.dictionary, call_tree_t{{{}, {0}}},
        tokens_t{token_t{token_type::macro_pf, "_func"}},
        [](translate_state_t &state) {
            namespace df = dictionary_funcs;

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
                            df::value(state, state.tokens[state.index].value, value_type::string)
                    })
            }));

            for (auto arg_index : state.tree.src[state.index]) {
                auto token_value_type = value_from_token_type(state.tokens[arg_index].type);
                tree_src_element_t arg_b_id;
                if (token_value_type != value_type::func_name) {
                    arg_b_id = df::function_name(state, "b");
                    auto type_id = df::function_name(state, cutvm_type_from_value_type(token_value_type));
                    df::function(state, arg_b_id, {
                            df::function(state, type_id, {
                                    df::value(state, state.tokens[arg_index].value, token_value_type)
                            })
                    });
                } else {
                    translate_state_t child_state = state;
                    child_state.index = arg_index;
                    arg_b_id = translate_function_call(child_state);
                }
                state.index_reference[arg_index] = arg_b_id;
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
        });
}