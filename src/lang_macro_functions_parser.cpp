#include "context_methods.hpp"
#include "lang_macro_functions_parser.hpp"

using namespace cuttle;

void lang::get_macro_functions_parser(context_t &context) {
    add(context, "0get", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);
    add(context, "0set", function_t{ function_type::prefix, 2 }, FUNCTION_ID_UNKNOWN);
    add(context, "0eq", function_t{ function_type::infix, 2 }, FUNCTION_ID_UNKNOWN);
    add(context, "0do", function_t{ function_type::postprefix, 0 }, FUNCTION_ID_UNKNOWN, "0end");
    add(context, "0if", function_t{ function_type::prefix, 2 }, FUNCTION_ID_UNKNOWN);
    add(context, "0else", function_t{ function_type::infix, 2 }, FUNCTION_ID_UNKNOWN);
}
