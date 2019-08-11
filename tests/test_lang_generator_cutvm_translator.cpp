#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>

#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "translator_methods.hpp"
#include "lang_generator_cutvm_translator.hpp"
#include "value_methods.hpp"

using namespace cuttle;

struct lang_generator_cutvm_translator_init_fixture {
    translator_t translator;
    values_t values;
    call_tree_t new_tree;

    void setup() {
        lang::get_lang_generator_cutvm_translator(translator);
    }
};

BOOST_FIXTURE_TEST_SUITE(lang_generator_can_translate_basic_rules_suite, lang_generator_cutvm_translator_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        tokens_t tokens = {
                {token_type::string, "", 0, 0},
                {token_type::atom,   "->", 0, 0},
                {token_type::string, ",", 0, 0},
                {token_type::atom,   "<-", 0, 0},
                {token_type::string, " ", 0, 0}
        };
        call_tree_t tree = {
                {
                        {}, {0, 3}, {}, {2, 4}, {}, {1}
                }, {}
        };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {1, 4, 8, 11, 15, 18},
                {2},
                {3},
                {},
                {5, 6, 7},
                {},
                {},
                {},
                {9},
                {10},
                {},
                {12, 13, 14},
                {},
                {},
                {},
                {16},
                {17},
                {},
                {19, 20, 21},
                {},
                {},
                {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"call", value_type::func_name},
                {"b",    value_type::func_name},
                {"s",    value_type::func_name},
                {"",    value_type::string},
                {"c",    value_type::func_name},
                {"1",    value_type::number},
                {"1",    value_type::number},
                {"before", value_type::func_name},
                {"b",    value_type::func_name},
                {"s",    value_type::func_name},
                {",",    value_type::string},
                {"c",    value_type::func_name},
                {"1",    value_type::number},
                {"1",    value_type::number},
                {"name", value_type::func_name},
                {"b",    value_type::func_name},
                {"s",    value_type::func_name},
                {" ",    value_type::string},
                {"c",    value_type::func_name},
                {"1",    value_type::number},
                {"1",    value_type::number},
                {"after", value_type::func_name},
        }));
    }

BOOST_AUTO_TEST_SUITE_END()