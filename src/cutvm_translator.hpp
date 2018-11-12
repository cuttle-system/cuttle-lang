#pragma once

#include "translator.hpp"

#define CUTTLE_CUTVM_CALL_TREE_NIL "__cuttle_call_tree_nil"

namespace cuttle {
    namespace lang {
        void get_cutvm_translator(translator_t &translator);
    }
}