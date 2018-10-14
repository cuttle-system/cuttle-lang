#include "lang_config_cutc_parser.hpp"
#include "lang_parser_base.hpp"
#include "context_methods.hpp"

using namespace cuttle;

void lang::get_config_cutc_parser(context_t &context) {
    get_parser_base(context);

    add(context, ".", function_t{function_type::infix, 2}, FUNCTION_ID_UNKNOWN);

    add(context, "just", function_t{function_type::prefix, 1}, FUNCTION_ID_UNKNOWN);
    add(context, "to", function_t{function_type::infix, 2}, FUNCTION_ID_UNKNOWN);
}
