#pragma once

#include "value.hpp"
#include "unsupported_cutvm_type_error.hpp"

namespace cuttle {
    const char *cutvm_type_from_value_type(const value_type &value_type);
}