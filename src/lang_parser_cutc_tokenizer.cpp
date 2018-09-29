#include "context_methods.hpp"
#include "lang_parser_base.hpp"
#include "lang_parser_cutc_tokenizer.hpp"

using namespace cuttle;

void lang::get_parser_cutc_tokenizer(context_t &context) {
    get_parser_base(context);
    add(context, "->", function_t{ function_type::infix, 2 }, 3);
    add(context, "normal_string", function_t{ function_type::prefix, 1 }, 4);
}