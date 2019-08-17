#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>

#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "translator_methods.hpp"
#include "lang_parser_cutvm_translator.hpp"
#include "value_methods.hpp"

using namespace cuttle;

struct lang_parser_cutvm_translator_init_fixture {
    translator_t translator;
    values_t values;
    call_tree_t new_tree;

    void setup() {
        lang::get_lang_parser_cutvm_translator(translator);
    }
};

BOOST_FIXTURE_TEST_SUITE(lang_parser_can_translate_basic_rules_suite, lang_parser_cutvm_translator_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        tokens_t tokens = {
                {token_type::atom,   "postfix", 0, 0},
                {token_type::string, ";",       0, 0},
                {token_type::atom,   "before",  0, 0},
                {token_type::string, "return",  0, 0},
        };
        call_tree_t tree = {
                {
                        {1, 2}, {}, {3}, {}, {0}
                },
                {}
        };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {1,  4,  7, 11, 18},
                {2},
                {3},
                {},
                {5},
                {6},
                {},
                {8},
                {9},
                {},
                {},
                {12, 15},
                {13},
                {14},
                {},
                {16, 17, 10},
                {},
                {},
                {19, 20, 21},
                {},
                {},
                {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"call",                   value_type::func_name},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {";",                      value_type::string},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {"postfix",                value_type::func_name},
                {"b",                      value_type::func_name},
                {"i",                      value_type::func_name},
                {"0",                      value_type::number},
                {"before",                   value_type::func_name},
                {"call",                   value_type::func_name},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {"return",                 value_type::string},
                {"c",                      value_type::func_name},
                {"1",                      value_type::number},
                {"1",                      value_type::number},
                {"c",                      value_type::func_name},
                {"4",                      value_type::number},
                {"4",                      value_type::number},
                {"add_parser_config_rule", value_type::func_name},
        }));
    }

    BOOST_AUTO_TEST_CASE(case2) {
        tokens_t tokens = {
                {token_type::atom,   "prefix", 0, 0},
                {token_type::string, ";",      0, 0},
                {token_type::atom,   "root",   0, 0},
        };
        call_tree_t tree = {
                {
                        {1, 2}, {}, {}, {0}
                },
                {}
        };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {1,  4,  7, 11, 15},
                {2},
                {3},
                {},
                {5},
                {6},
                {},
                {8},
                {9},
                {},
                {},
                {12},
                {13, 14, 10},
                {},
                {},
                {16, 17, 18},
                {},
                {},
                {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"call",                   value_type::func_name},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {";",                      value_type::string},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {"prefix",                 value_type::func_name},
                {"b",                      value_type::func_name},
                {"i",                      value_type::func_name},
                {"0",                      value_type::number},
                {"root",                      value_type::func_name},
                {"call",                   value_type::func_name},
                {"c",                      value_type::func_name},
                {"0",                      value_type::number},
                {"0",                      value_type::number},
                {"c",                      value_type::func_name},
                {"4",                      value_type::number},
                {"4",                      value_type::number},
                {"add_parser_config_rule", value_type::func_name},
        }));
    }

    BOOST_AUTO_TEST_CASE(case3) {
        tokens_t tokens = {
                {token_type::atom,   "prefix", 0, 0},
                {token_type::string, ";",      0, 0},
                {token_type::atom,   "..",     0, 0},
                {token_type::number, "2",      0, 0},
                {token_type::atom,   "root",   0, 0},
        };
        call_tree_t tree = {
                {
                        {1, 2, 4}, {}, {3}, {}, {}, {0}
                },
                {}
        };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {1,  4,  7, 11, 15},
                {2},
                {3},
                {},
                {5},
                {6},
                {},
                {8},
                {9},
                {},
                {},
                {12},
                {13, 14, 10},
                {},
                {},
                {16, 17, 18},
                {},
                {},
                {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"call",                   value_type::func_name},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {";",                      value_type::string},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {"prefix",                 value_type::func_name},
                {"b",                      value_type::func_name},
                {"i",                      value_type::func_name},
                {"2",                      value_type::number},
                {"root",                      value_type::func_name},
                {"call",                   value_type::func_name},
                {"c",                      value_type::func_name},
                {"0",                      value_type::number},
                {"0",                      value_type::number},
                {"c",                      value_type::func_name},
                {"4",                      value_type::number},
                {"4",                      value_type::number},
                {"add_parser_config_rule", value_type::func_name},
        }));
    }

    BOOST_AUTO_TEST_CASE(case4) {
        tokens_t tokens = {
                {token_type::atom,   "prefix", 0, 0},
                {token_type::string, ";",      0, 0},
                {token_type::atom,   "..",     0, 0},
                {token_type::number, "2",      0, 0},
                {token_type::atom,   "before", 0, 0},
                {token_type::string, "foo",    0, 0},
        };
        call_tree_t tree = {
                {
                        {1, 2, 4}, {}, {3}, {}, {5}, {}, {0}
                },
                {}
        };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {1,  4,  7, 11, 18},
                {2},
                {3},
                {},
                {5},
                {6},
                {},
                {8},
                {9},
                {},
                {},
                {12, 15},
                {13},
                {14},
                {},
                {16, 17, 10},
                {},
                {},
                {19, 20, 21},
                {},
                {},
                {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"call",                   value_type::func_name},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {";",                      value_type::string},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {"prefix",                 value_type::func_name},
                {"b",                      value_type::func_name},
                {"i",                      value_type::func_name},
                {"2",                      value_type::number},
                {"before",                   value_type::func_name},
                {"call",                   value_type::func_name},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {"foo",                 value_type::string},
                {"c",                      value_type::func_name},
                {"1",                      value_type::number},
                {"1",                      value_type::number},
                {"c",                      value_type::func_name},
                {"4",                      value_type::number},
                {"4",                      value_type::number},
                {"add_parser_config_rule", value_type::func_name},
        }));
    }

    BOOST_AUTO_TEST_CASE(case5) {
        tokens_t tokens = {
                {token_type::atom,   "postprefix", 0, 0},
                {token_type::string, "(",          0, 0},
                {token_type::atom,   "->",         0, 0},
                {token_type::string, ")",          0, 0},
                {token_type::atom,   "before",     0, 0},
                {token_type::string, "foo",        0, 0},
        };
        call_tree_t tree = {
                {
                        {2, 4}, {}, {1, 3}, {}, {5}, {}, {0}
                },
                {}
        };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {2, 12, 15, 19, 26},
                {},
                {3, 6, 9},
                {4},
                {5},
                {},
                {7},
                {8},
                {},
                {10, 11, 1},
                {},
                {},
                {13},
                {14},
                {},
                {16},
                {17},
                {},
                {},
                {20, 23},
                {21},
                {22},
                {},
                {24, 25, 18},
                {},
                {},
                {27, 28, 29},
                {},
                {},
                {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"call",                   value_type::func_name},
                {"->",                   value_type::func_name},
                {"call",                   value_type::func_name},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {"(",                 value_type::string},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {")",                 value_type::string},
                {"c",                      value_type::func_name},
                {"2",                      value_type::number},
                {"2",                      value_type::number},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {"postprefix",                 value_type::func_name},
                {"b",                      value_type::func_name},
                {"i",                      value_type::func_name},
                {"0",                      value_type::number},
                {"before",                   value_type::func_name},
                {"call",                   value_type::func_name},
                {"b",                      value_type::func_name},
                {"s",                      value_type::func_name},
                {"foo",                 value_type::string},
                {"c",                      value_type::func_name},
                {"1",                      value_type::number},
                {"1",                      value_type::number},
                {"c",                      value_type::func_name},
                {"4",                      value_type::number},
                {"4",                      value_type::number},
                {"add_parser_config_rule", value_type::func_name},
        }));
    }

// TODO: implement type system for translator functions (return type, argument types, e.g.)

//    BOOST_AUTO_TEST_CASE(case3) {
//        tokens_t tokens = {
//                {token_type::number, "1", 0, 0},
//                {token_type::atom,   "+", 0, 0},
//                {token_type::number, "2", 0, 0}
//        };
//        call_tree_t tree = {
//                {
//                        {}, {0, 2}, {}, {1}
//                },
//                {}
//        };
//        translate(translator, tokens, tree, values, new_tree);
//        BOOST_CHECK(new_tree.src == (tree_src_t{
//                {},
//                {2, 5,  8},
//                {3},
//                {4},
//                {},
//                {6},
//                {7},
//                {},
//                {9, 10, 0},
//                {},
//                {},
//                {1}
//        }));
//        BOOST_CHECK(values == (values_t{
//                {"+",    value_type::func_name},
//                {"call", value_type::func_name},
//                {"b",    value_type::func_name},
//                {"i",    value_type::func_name},
//                {"1",    value_type::number},
//                {"b",    value_type::func_name},
//                {"i",    value_type::func_name},
//                {"2",    value_type::number},
//                {"c",    value_type::func_name},
//                {"2",    value_type::number},
//                {"2",    value_type::number}
//        }));
//    }

BOOST_AUTO_TEST_SUITE_END()
