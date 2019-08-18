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
                        {"3", value_type::number},
                        {"0", value_type::number},
                        {"array", value_type::func_name}
                }};
        call_tree_t tree = {
                {
                        {1, 4, 7, 10},
                        {2}, {3}, {},
                        {5}, {6}, {},
                        {8}, {9}, {},
                        {11, 12, 13}, {}, {}, {}, {0}
                },
                {}};

        generate(tokenizer_config, generator_config, context, values, tree, state);
        BOOST_CHECK_EQUAL(state.output, "b s +\n"
                                        "b i 1\n"
                                        "b i 2\n"
                                        "c 3 0 array");
    }

    BOOST_AUTO_TEST_CASE(case2) {
        values_t values = {
                {
                        {"call", value_type::func_name},
                        {"b", value_type::func_name}, {"s", value_type::func_name}, {"+", value_type::string},
                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"1", value_type::number},

                        {"call", value_type::func_name},
                        {"b", value_type::func_name}, {"s", value_type::func_name}, {"foo", value_type::string},
                        {"c", value_type::func_name},
                        {"1", value_type::number},
                        {"0", value_type::number},
                        {"array", value_type::func_name},

                        {"c", value_type::func_name},
                        {"3", value_type::number},
                        {"0", value_type::number},
                        {"array", value_type::func_name}
                }};
        call_tree_t tree = {
                {
                        {1, 4, 7, 15},
                        {2}, {3}, {},
                        {5}, {6}, {},

                        {8, 11},
                        {9}, {10}, {},
                        {12, 13, 14}, {}, {}, {},

                        {16, 17, 18}, {}, {}, {},
                        {0}
                },
                {}};

        generate(tokenizer_config, generator_config, context, values, tree, state);
        BOOST_CHECK_EQUAL(state.output, "b s +\n"
                                        "b i 1\n"
                                        "b s foo\n"
                                        "c 1 0 array\n"
                                        "c 3 0 array");
    }

    BOOST_AUTO_TEST_CASE(case3) {
        values_t values = {
                {
                        {"call", value_type::func_name},
                        {"b", value_type::func_name}, {"s", value_type::func_name}, {"+", value_type::string},
                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"1", value_type::number},

                        {"call", value_type::func_name},
                        {"b", value_type::func_name}, {"s", value_type::func_name}, {"foo", value_type::string},

                        {"call", value_type::func_name},
                        {"b", value_type::func_name}, {"s", value_type::func_name}, {"-", value_type::string},
                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"1", value_type::number},
                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"2", value_type::number},
                        {"c", value_type::func_name},
                        {"3", value_type::number},
                        {"0", value_type::number},
                        {"array", value_type::func_name},

                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"3", value_type::number},

                        {"c", value_type::func_name},
                        {"3", value_type::number},
                        {"0", value_type::number},
                        {"array", value_type::func_name},

                        {"c", value_type::func_name},
                        {"3", value_type::number},
                        {"0", value_type::number},
                        {"array", value_type::func_name}
                }};
        call_tree_t tree = {
                {
                        {1, 4, 7, 32},
                        {2}, {3}, {},
                        {5}, {6}, {},

                        {8, 11, 25, 28},
                        {9}, {10}, {},

                        {12, 15, 18, 21},
                        {13}, {14}, {},
                        {16}, {17}, {},
                        {19}, {20}, {},
                        {22, 23, 24}, {}, {}, {},

                        {26}, {27}, {},
                        {29, 30, 31}, {}, {}, {},

                        {33, 34, 35}, {}, {}, {},
                        {0}
                },
                {}};

        generate(tokenizer_config, generator_config, context, values, tree, state);
        BOOST_CHECK_EQUAL(state.output, "b s +\n"
                                        "b i 1\n"
                                        "b s foo\n"
                                        "b s -\n"
                                        "b i 1\n"
                                        "b i 2\n"
                                        "c 3 0 array\n"
                                        "b i 3\n"
                                        "c 3 0 array\n"
                                        "c 3 0 array");
    }

    BOOST_AUTO_TEST_CASE(case4) {
        values_t values = {
                {
                        {"call", value_type::func_name},
                        {"b", value_type::func_name}, {"s", value_type::func_name}, {"+", value_type::string},
                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"1", value_type::number},
                        {"call", value_type::func_name},
                        {"c", value_type::func_name}, {"3", value_type::number}, {"0", value_type::number}, {"array", value_type::func_name},

                        {"b", value_type::func_name}, {"s", value_type::func_name}, {"-", value_type::string},
                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"2", value_type::number},
                        {"b", value_type::func_name}, {"i", value_type::func_name}, {"2", value_type::number},
                        {"c", value_type::func_name}, {"3", value_type::number}, {"0", value_type::number}, {"array", value_type::func_name}
                }};
        call_tree_t tree = {
                {
                        {1, 4, 7, 8},
                        {2}, {3}, {},
                        {5}, {6}, {},
                        {12, 15, 18, 21},
                        {9, 10, 11}, {}, {}, {},

                        {13}, {14}, {},
                        {16}, {17}, {},
                        {19}, {20}, {},
                        {22, 23, 24}, {}, {}, {},
                        {0}
                },
                {}};

        generate(tokenizer_config, generator_config, context, values, tree, state);
        BOOST_CHECK_EQUAL(state.output, "b s +\n"
                                        "b i 1\n"
                                        "b s -\n"
                                        "b i 2\n"
                                        "b i 2\n"
                                        "c 3 0 array\n"
                                        "c 3 0 array");
    }

BOOST_AUTO_TEST_SUITE_END()