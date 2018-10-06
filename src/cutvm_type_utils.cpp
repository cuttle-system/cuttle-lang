#include "cutvm_type_utils.hpp"

const char *cuttle::cutvm_type_from_value_type(const value_type &value_type) {
    switch (value_type) {
        case value_type::func_name:
            return "s";
        case value_type::number:
            return "i";
        case value_type::string:
            return "s";
        default:
            throw unsupported_cutvm_type_error(value_type);
    }
}