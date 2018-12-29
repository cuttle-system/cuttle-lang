#include "cutvm_type_utils.hpp"
#include "value.hpp"

const char *cuttle::cutvm_type_from_value_type(const value_type &type) {
    switch (type) {
        case value_type::number:
            return "i";
        default:
            return "s";
    }
}