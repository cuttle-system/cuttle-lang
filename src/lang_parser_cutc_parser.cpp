#include "context_methods.hpp"
#include "lang_parser_base.hpp"
#include "lang_parser_cutc_parser.hpp"

using namespace cuttle;

void lang::get_parser_cutc_parser(context_t &context) {
    get_parser_base(context);

    add(context, "->", function_t{ function_type::infix, 2 }, FUNCTION_ID_UNKNOWN);

    add(context, "..", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);
    add(context, "...", function_t{ function_type::prefix, 0 }, FUNCTION_ID_UNKNOWN);

    add(context, "before", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);
    add(context, "root", function_t{ function_type::prefix, 0 }, FUNCTION_ID_UNKNOWN);

    add(context, "prefix", function_t{ function_type::prefix, 3 }, FUNCTION_ID_UNKNOWN);
    add(context, "infix", function_t{ function_type::prefix, 2 }, FUNCTION_ID_UNKNOWN);
    add(context, "postfix", function_t{ function_type::prefix, 2 }, FUNCTION_ID_UNKNOWN);
    add(context, "postprefix", function_t{ function_type::prefix, 2 }, FUNCTION_ID_UNKNOWN);
    add(context, "postinfix", function_t{ function_type::prefix, 2 }, FUNCTION_ID_UNKNOWN);
}
