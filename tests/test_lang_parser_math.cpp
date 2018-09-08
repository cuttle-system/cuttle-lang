#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>
#include "token.hpp"
#include "parser.hpp"
#include "context_methods.hpp"
#include "lang_parser_base.hpp"

using namespace cuttle;
using namespace cuttle::lang;

struct context_init_fixture {
    context_t context;
    call_tree_t tree;

    void setup() {
        initialize(context);
        get_parser_base(context);
    }
};

BOOST_FIXTURE_TEST_SUITE(lang_parser_math_suite, context_init_fixture)

    BOOST_AUTO_TEST_CASE(plus) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "2", 1, 1},
                token_t {token_type::atom, "+", 1, 3},
                token_t {token_type::number, "2", 1, 5}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1} }));
    }

    BOOST_AUTO_TEST_CASE(minus) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "7", 1, 1},
                token_t {token_type::atom, "-", 1, 3},
                token_t {token_type::number, "1", 1, 5}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1} }));
    }

    BOOST_AUTO_TEST_CASE(multiply) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "123", 1, 1},
                token_t {token_type::atom, "*", 1, 5},
                token_t {token_type::number, "5", 1, 7}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1} }));
    }

    BOOST_AUTO_TEST_CASE(divide) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "7", 1, 1},
                token_t {token_type::atom, "/", 1, 3},
                token_t {token_type::number, "2", 1, 5}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1} }));
    }

    BOOST_AUTO_TEST_CASE(plus_and_minus) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "1", 1, 1},
                token_t {token_type::atom, "+", 1, 3},
                token_t {token_type::number, "2", 1, 5},
                token_t {token_type::atom, "-", 1, 7},
                token_t {token_type::number, "8", 1, 9}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1, 4}, {}, {3} }));
    }

    BOOST_AUTO_TEST_CASE(multiply_and_divide) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "7", 1, 1},
                token_t {token_type::atom, "*", 1, 3},
                token_t {token_type::number, "2", 1, 5},
                token_t {token_type::atom, "/", 1, 7},
                token_t {token_type::number, "8", 1, 9}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1, 4}, {}, {3} }));
    }

    BOOST_AUTO_TEST_CASE(multiply_and_plus) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "7", 1, 1},
                token_t {token_type::atom, "*", 1, 3},
                token_t {token_type::number, "2", 1, 5},
                token_t {token_type::atom, "+", 1, 7},
                token_t {token_type::number, "8", 1, 9}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1, 4}, {}, {3} }));
    }

    BOOST_AUTO_TEST_CASE(divide_and_plus) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "7", 1, 1},
                token_t {token_type::atom, "/", 1, 3},
                token_t {token_type::number, "2", 1, 5},
                token_t {token_type::atom, "+", 1, 7},
                token_t {token_type::number, "8", 1, 9}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1, 4}, {}, {3} }));
    }

    BOOST_AUTO_TEST_CASE(multiply_and_minus) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "7", 1, 1},
                token_t {token_type::atom, "*", 1, 3},
                token_t {token_type::number, "2", 1, 5},
                token_t {token_type::atom, "+", 1, 7},
                token_t {token_type::number, "8", 1, 9}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1, 4}, {}, {3} }));
    }

    BOOST_AUTO_TEST_CASE(divide_and_minus) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "7", 1, 1},
                token_t {token_type::atom, "/", 1, 3},
                token_t {token_type::number, "2", 1, 5},
                token_t {token_type::atom, "-", 1, 7},
                token_t {token_type::number, "8", 1, 9}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1, 4}, {}, {3} }));
    }

    BOOST_AUTO_TEST_CASE(divide_minus_and_multiply) {
        std::vector<token_t> tokens = {
                token_t {token_type::number, "7", 1, 1},
                token_t {token_type::atom, "/", 1, 3},
                token_t {token_type::number, "2", 1, 5},
                token_t {token_type::atom, "-", 1, 7},
                token_t {token_type::number, "8", 1, 9},
                token_t {token_type::atom, "*", 1, 11},
                token_t {token_type::number, "8", 1, 13}
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {}, {0, 2}, {}, {1, 5}, {}, {4, 6}, {}, {3} }));
    }

BOOST_AUTO_TEST_SUITE_END()