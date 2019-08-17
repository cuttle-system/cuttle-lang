#pragma once

#include "translator.hpp"

namespace cuttle {
    namespace lang {
        void get_lang_cutvm_translator(translator_t &translator);

        tree_src_element_t cutvm_function_call(translate_state_t &state,
                                               tree_src_element_t function_name,
                                               const std::vector<tree_src_element_t> &initial_args_indexes
        );

        tree_src_element_t cutvm_push_value_to_stack(translate_state_t &state);
    }
}