#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>
#include "token.hpp"
#include "parser.hpp"
#include "context_methods.hpp"
#include "lang_parser_cutc_parser.hpp"

using namespace cuttle;
using namespace cuttle::lang;

struct context_init_fixture {
    context_t context;
    call_tree_t tree;

    void setup() {
        initialize(context);
        get_parser_cutc_parser(context);
    }
};

BOOST_FIXTURE_TEST_SUITE(lang_parser_cutc_parser_suite, context_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        std::vector<token_t> tokens = {
                token_t {token_type::atom, "prefix", 1, 1},
                token_t {token_type::string, "+", 1, 7},
                token_t {token_type::atom, "...", 1, 10},
                token_t {token_type::atom, "root", 1, 14}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {1, 2, 3}, {}, {}, {}, {0} }));
    }

    BOOST_AUTO_TEST_CASE(case2) {
        std::vector<token_t> tokens = {
                token_t {token_type::atom, "prefix", 1, 1},
                token_t {token_type::string, "+", 1, 7},
                token_t {token_type::atom, "..", 1, 10},
                token_t {token_type::number, "2", 1, 13},
                token_t {token_type::atom, "root", 1, 15}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {1, 2, 4}, {}, {3}, {}, {}, {0} }));
    }

    BOOST_AUTO_TEST_CASE(case3) {
        std::vector<token_t> tokens = {
                token_t {token_type::atom, "prefix", 1, 1},
                token_t {token_type::string, "+", 1, 7},
                token_t {token_type::atom, "..", 1, 10},
                token_t {token_type::number, "2", 1, 13},
                token_t {token_type::atom, "before", 1, 15},
                token_t {token_type::string, "foo", 1, 23}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {1, 2, 4}, {}, {3}, {}, {5}, {}, {0} }));
    }

    BOOST_AUTO_TEST_CASE(case4) {
        std::vector<token_t> tokens = {
                token_t {token_type::atom, "infix", 1, 1},
                token_t {token_type::string, "-", 1, 7},
                token_t {token_type::atom, "before", 1, 15},
                token_t {token_type::string, "foo", 1, 23}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {1, 2}, {}, {3}, {}, {0} }));
    }


    BOOST_AUTO_TEST_CASE(case5) {
        std::vector<token_t> tokens = {
                token_t {token_type::atom, "postprefix", 1, 1},
                token_t {token_type::string, "(", 1, 7},
                token_t {token_type::atom, "->", 1, 8},
                token_t {token_type::string, ")", 1, 12},
                token_t {token_type::atom, "before", 1, 15},
                token_t {token_type::string, "foo", 1, 23}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {2, 4}, {}, {1, 3}, {}, {5}, {}, {0} }));
    }

BOOST_AUTO_TEST_SUITE_END()