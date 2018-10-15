#include "context_methods.hpp"
#include "lang_parser_base.hpp"
#include "lang_tokenizer_cutc_parser.hpp"

using namespace cuttle;

void lang::get_tokenizer_cutc_parser(context_t &context) {
    get_parser_base(context);
    add(context, "->", function_t{ function_type::infix, 2 }, 3);
    add(context, "normal_string", function_t{ function_type::prefix, 1 }, 4);
    add(context, "formatted_string", function_t{ function_type::prefix, 1 }, 4);
    add(context, "comments", function_t{ function_type::prefix, 1 }, 4);
    add(context, "macro_ps", function_t{ function_type::prefix, 1 }, 4);
    add(context, "macro_pf", function_t{ function_type::prefix, 1 }, 4);
    add(context, "macro_p", function_t{ function_type::prefix, 1 }, 4);

    add(context, "separated_symbol", function_t{ function_type::prefix, 1 }, 4);
    add(context, "macro_if", function_t{ function_type::prefix, 1 }, 4);

    add(context, "formatted_characters", function_t{ function_type::prefix, 1 }, 4);

    add(context, "separate_digit_and_alpha", function_t{ function_type::prefix, 1 }, 4);
}
