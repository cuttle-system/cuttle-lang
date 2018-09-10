#pragma once

#include <stdexcept>
#include <sstream>
#include <string>
#include "value_methods.hpp"

namespace cuttle {
	class unsupported_cutvm_type_error : public std::logic_error {
	public:
	    static std::string value_type_to_string(const value_type &type) {
            std::stringstream sstr;
            sstr << type;
            return sstr.str();
	    }

		explicit unsupported_cutvm_type_error(const value_type &type)
		: logic_error("Type is not supported by the vm: " + value_type_to_string(type)) {}
	};
}