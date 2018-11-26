#pragma once

#include "translator.hpp"
#include "cutvm_translator_nil.hpp"

namespace cuttle {
    namespace lang {
        void get_cutvm_translator(translator_t &translator);
    }
}