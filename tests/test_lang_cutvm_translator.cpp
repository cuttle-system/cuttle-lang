#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>

#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "translator_methods.hpp"
#include "lang_cutvm_translator.hpp"
#include "value_methods.hpp"

using namespace cuttle;

struct lang_cutvm_translator_init_fixture {
    translator_t translator;
    values_t values;
    call_tree_t new_tree;

    void setup() {
        lang::get_lang_cutvm_translator(translator);
    }
};

BOOST_FIXTURE_TEST_SUITE(lang_can_translate_basic_function_calls_suite, lang_cutvm_translator_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        tokens_t tokens = {
                {token_type::number, "1", 0, 0},
                {token_type::atom,   "+", 0, 0},
                {token_type::number, "2", 0, 0}
        };
        call_tree_t tree = {
                {
                        {}, {0, 2}, {}, {1}
                }
        };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {},
                {2,  5,  8},
                {3},
                {4},
                {},
                {6},
                {7},
                {},
                {9, 10, 0},
                {},
                {},
                {1}
        }));
        BOOST_CHECK(values == (values_t{
                {"+",    value_type::func_name},
                {"call", value_type::func_name},
                {"b",    value_type::func_name},
                {"i",    value_type::func_name},
                {"1",    value_type::number},
                {"b",    value_type::func_name},
                {"i",    value_type::func_name},
                {"2",    value_type::number},
                {"c",    value_type::func_name},
                {"2",    value_type::number},
                {"2",    value_type::number}
        }));
    }

BOOST_AUTO_TEST_SUITE_END()

struct lang_parser_cutvm_translator_init_fixture {
    translator_t translator;
    values_t values;
    call_tree_t new_tree;

    void setup() {
        lang::get_lang_parser_cutvm_translator(translator);
    }
};

BOOST_FIXTURE_TEST_SUITE(lang_parser_can_translate_basic_function_calls_suite, lang_parser_cutvm_translator_init_fixture
)

    BOOST_AUTO_TEST_CASE(case1) {
        tokens_t tokens = {
                {token_type::number, "1", 0, 0},
                {token_type::atom,   "+", 0, 0},
                {token_type::number, "2", 0, 0}
        };
        call_tree_t tree = {
                {
                        {}, {0, 2}, {}, {1}
                }
        };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {},
                {2,  5,  8},
                {3},
                {4},
                {},
                {6},
                {7},
                {},
                {9, 10, 0},
                {},
                {},
                {1}
        }));
        BOOST_CHECK(values == (values_t{
                {"+",    value_type::func_name},
                {"call", value_type::func_name},
                {"b",    value_type::func_name},
                {"i",    value_type::func_name},
                {"1",    value_type::number},
                {"b",    value_type::func_name},
                {"i",    value_type::func_name},
                {"2",    value_type::number},
                {"c",    value_type::func_name},
                {"2",    value_type::number},
                {"2",    value_type::number}
        }));
    }

    BOOST_AUTO_TEST_CASE(case2) {
        tokens_t tokens = {
                {token_type::atom, "priority_after", 0, 0},
                {token_type::number, "5",              0, 0}
        };
        call_tree_t tree = {
                {
                        {1}, {}, {0}
                }
        };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {},
                {2,  5},
                {3},
                {4},
                {},
                {6, 7, 0},
                {},
                {},
                {1}
        }));
        BOOST_CHECK(values == (values_t{
                {"priority_after", value_type::func_name},
                {"call",           value_type::func_name},
                {"b",              value_type::func_name},
                {"i",              value_type::func_name},
                {"5",              value_type::number},
                {"c",              value_type::func_name},
                {"1",              value_type::number},
                {"1",              value_type::number}
        }));
    }


BOOST_AUTO_TEST_SUITE_END()
