#include "context_methods.hpp"
#include "lang_parser_base.hpp"
#include "lang_parser_cutc_parser.hpp"

using namespace cuttle;

void lang::get_parser_cutc_parser(context_t &context) {
    get_parser_base(context);

    add(context, "name", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);

    add(context, "type", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);
    add(context, "prefix", function_t{ function_type::prefix, 0 }, FUNCTION_ID_UNKNOWN);
    add(context, "infix", function_t{ function_type::prefix, 0 }, FUNCTION_ID_UNKNOWN);
    add(context, "postfix", function_t{ function_type::prefix, 0 }, FUNCTION_ID_UNKNOWN);

    add(context, "args_number", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);

    add(context, "executes_before", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);
    add(context, "func_id", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);
    add(context, "start_func_id", function_t{ function_type::prefix, 0 }, FUNCTION_ID_UNKNOWN);
}
