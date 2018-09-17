#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>
#include "cutvm_tokenizer.hpp"
#include "generator_methods.hpp"
#include "cutvm_context.hpp"
#include "cutvm_generator.hpp"
#include "value_methods.hpp"
#include "context_methods.hpp"

using namespace cuttle;

struct cutvm_generator_init_fixture {
    context_t context;
    generator_state_t state;
    tokenizer_config_t tokenizer_config;
    generator_config_t generator_config;

    void setup() {
        initialize(context);
        initialize(state);
        lang::get_cutvm_context(context);
        lang::get_cutvm_tokenizer_config(tokenizer_config);
        lang::get_cutvm_generator_config(generator_config);
    }
};

BOOST_FIXTURE_TEST_SUITE(generates_basic_cutvm_code_suite, cutvm_generator_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        values_t values = {
                {
                        {"call", value_type::func_name},
                        {"b", value_type::func_name}, {"s", value_type::func_name}, {"+", value_type::string},
                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"1", value_type::number},
                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"2", value_type::number},

                        {"c", value_type::func_name},
                                {"0", value_type::number},
                                {"3", value_type::number},
                                {"array", value_type::func_name}
                }};
        call_tree_t tree = {
                {
                        {1, 4, 7, 10},
                        {2}, {3}, {},
                        {5}, {6}, {},
                        {8}, {9}, {},
                        {11, 12, 13}, {}, {}, {}, {0}
                }};

        generate(tokenizer_config, generator_config, context, values, tree, state);
        BOOST_CHECK_EQUAL(state.output, "b s +\n"
                                        "b i 1\n"
                                        "b i 2\n"
                                        "c 0 3 array");
    }

BOOST_AUTO_TEST_SUITE_END()