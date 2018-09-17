#include "context_methods.hpp"
#include "cutvm_context.hpp"

void cuttle::lang::get_cutvm_context(context_t &context) {
    add(context, "i", {function_type::prefix, 1}, FUNCTION_ID_UNKNOWN);
    add(context, "s", {function_type::prefix, 1}, FUNCTION_ID_UNKNOWN);
    add(context, "b", {function_type::prefix, 1}, FUNCTION_ID_UNKNOWN);
    add(context, "c", {function_type::prefix, 3}, FUNCTION_ID_UNKNOWN);
}