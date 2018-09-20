#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>
#include "translator_methods.hpp"
#include "cutvm_translator.hpp"
#include "value_methods.hpp"

using namespace cuttle;

struct cutvm_translator_init_fixture {
    translator_t translator;
    values_t values;
    call_tree_t new_tree;

    void setup() {
        lang::get_cutvm_translator(translator);
    }
};

BOOST_FIXTURE_TEST_SUITE(can_translate_basic_function_calls_suite, cutvm_translator_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        tokens_t tokens = {
                { token_type::number, "1", 0, 0 },
                { token_type::atom, "+", 0, 0 },
                { token_type::number, "2", 0, 0 }
        };
        call_tree_t tree = { {
                                     {}, {0, 2}, {}, {1}
                             } };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {1, 4, 7, 10},
                {2}, {3}, {},
                {5}, {6}, {},
                {8}, {9}, {},
                {11, 12, 13}, {}, {}, {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"call", value_type::func_name},
                {"b", value_type::func_name}, {"s", value_type::func_name}, {"+", value_type::string},
                {"b", value_type::func_name}, {"i", value_type::func_name}, {"1", value_type::number},
                {"b", value_type::func_name}, {"i", value_type::func_name}, {"2", value_type::number},

                {"c", value_type::func_name}, {"0", value_type::number}, {"3", value_type::number}, {"array", value_type::func_name}
        }));
    }

    BOOST_AUTO_TEST_CASE(case2) {
        tokens_t tokens = {
                { token_type::number, "1", 0, 0 },
                { token_type::atom, "+", 0, 0 },
                { token_type::number, "2", 0, 0 },
                { token_type::atom, "-", 0, 0 },
                { token_type::number, "2", 0, 0 }
        };
        call_tree_t tree = { {
                                     {}, {0, 3},
                                     {}, {2, 4}, {}, {1}
                             } };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
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
        }));
        BOOST_CHECK(values == (values_t{
                {"call", value_type::func_name},
                {"b", value_type::func_name}, {"s", value_type::func_name}, {"+", value_type::string},
                {"b", value_type::func_name}, {"i", value_type::func_name}, {"1", value_type::number},
                {"call", value_type::func_name},
                {"c", value_type::func_name}, {"0", value_type::number}, {"3", value_type::number}, {"array", value_type::func_name},

                {"b", value_type::func_name}, {"s", value_type::func_name}, {"-", value_type::string},
                {"b", value_type::func_name}, {"i", value_type::func_name}, {"2", value_type::number},
                {"b", value_type::func_name}, {"i", value_type::func_name}, {"2", value_type::number},
                {"c", value_type::func_name}, {"0", value_type::number}, {"3", value_type::number}, {"array", value_type::func_name}
        }));
    }

BOOST_AUTO_TEST_SUITE_END()
