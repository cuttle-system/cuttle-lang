#include "context_methods.hpp"
#include "lang_parser_base.hpp"
#include "lang_generator_arg_cutc_parser.hpp"

using namespace cuttle;

void lang::get_generator_arg_cutc_parser(context_t &context) {
    get_parser_base(context);

    add(context, "before", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);
    add(context, "after", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);
    add(context, "skip", function_t{ function_type::prefix, 1 }, FUNCTION_ID_UNKNOWN);
}
