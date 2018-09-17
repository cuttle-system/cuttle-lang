#include "generator_config.hpp"
#include "cutvm_generator.hpp"

void cuttle::lang::get_cutvm_generator_config(generator_config_t &generator_config) {
    generator_config.joined_functions = {"call"};
}