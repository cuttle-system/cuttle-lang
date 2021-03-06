#include "context_methods.hpp"
#include "lang_parser_base.hpp"

using namespace cuttle;

void get_parser_math(context_t &context) {
    add(context, "*", function_t{ function_type::infix, 2 }, FUNCTION_ID_UNKNOWN);
    add(context, "/", function_t{ function_type::infix, 2 }, FUNCTION_ID_UNKNOWN);
    add(context, "+", function_t{ function_type::infix, 2 }, FUNCTION_ID_UNKNOWN);
    add(context, "-", function_t{ function_type::infix, 2 }, FUNCTION_ID_UNKNOWN);
}

void get_parser_boolean(context_t &context) {
    add(context, "true", function_t{ function_type::prefix, 0}, FUNCTION_ID_UNKNOWN);
    add(context, "false", function_t{ function_type::prefix, 0}, FUNCTION_ID_UNKNOWN);
}

void lang::get_parser_base(context_t &context) {
    get_parser_math(context);
    get_parser_boolean(context);
}
