#include "value_methods.hpp"
#include "cutvm_translator.hpp"
#include "translator_methods.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "unsupported_cutvm_type_error.hpp"

using namespace cuttle;

const char *cutvm_type_from_value_type(const value_type &value_type) {
    switch (value_type) {
        case value_type::func_name:
            return "s";
        case value_type::number:
            return "i";
        case value_type::string:
            return "s";
        default:
            throw unsupported_cutvm_type_error(value_type);
    }
}

void lang::get_cutvm_translator(translator_t &translator) {
    dictionary_t dictionary;

    add(dictionary, TRANSLATOR_ANY_NAME, DICTIONARY_ANY_ARG_NUMBER, [](translate_state_t &state) {
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
            auto arg_b_id = df::function_name(state, "b");
            if (token_value_type != value_type::func_name) {
                auto type_id = df::function_name(state, cutvm_type_from_value_type(token_value_type));
                df::function(state, arg_b_id, {
                        df::function(state, type_id, {
                                df::value(state, state.tokens[arg_index].value, token_value_type)
                        })
                });
            }
            state.index_reference[arg_index] = arg_b_id;
            args_indexes.push_back(arg_b_id);
        }

        auto c_id = df::function_name(state, "c");
        args_indexes.push_back(df::function(state, c_id, {
                df::number(state, "0"),
                df::number(state, std::to_string(args_indexes.size())),
                df::function(state, df::function_name(state, "array"), {})
        }));

        df::function(state, call_id, args_indexes);

        return call_id;
    });

    translator = { { TRANSLATOR_ANY_NAME, TRANSLATOR_ANY_VERSION }, { "cutvm", 1 }, dictionary };
}