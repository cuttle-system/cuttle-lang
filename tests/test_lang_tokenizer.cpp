#define BOOST_TEST_DYN_LINK

#include "token.hpp"
#include "token_methods.hpp"
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>
#include "tokenizer.hpp"
#include "lang_tokenizer.hpp"

using namespace cuttle;

struct config_and_tokens_init_fixture {
    tokenizer_config_t config;
    tokens_t tokens;

    void setup() {
        lang::get_tokenizer_config(config);
    }
};

BOOST_FIXTURE_TEST_SUITE(can_tokenize_basic_function_calls_suite, config_and_tokens_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        tokenize(config, "foo 5 6", tokens);

        BOOST_CHECK_EQUAL(tokens[0].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[0].value, "foo");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK_EQUAL(tokens[1].type, token_type::number);
        BOOST_CHECK_EQUAL(tokens[1].value, "5");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 5);

        BOOST_CHECK_EQUAL(tokens[2].type, token_type::number);
        BOOST_CHECK_EQUAL(tokens[2].value, "6");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 7);
    }

    BOOST_AUTO_TEST_CASE(case2) {

        tokenize(config, "foo '5' 6", tokens);

        BOOST_CHECK_EQUAL(tokens[0].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[0].value, "foo");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK_EQUAL(tokens[1].type, token_type::string);
        BOOST_CHECK_EQUAL(tokens[1].value, "5");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 5);

        BOOST_CHECK_EQUAL(tokens[2].type, token_type::number);
        BOOST_CHECK_EQUAL(tokens[2].value, "6");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 9);
    }

    BOOST_AUTO_TEST_CASE(case3) {
        tokenizer_config_t config;
        tokens_t tokens;

        lang::get_tokenizer_config(config);

        tokenize(config, "foo '5' \"6\\n\"", tokens);

        BOOST_CHECK_EQUAL(tokens[0].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[0].value, "foo");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK_EQUAL(tokens[1].type, token_type::string);
        BOOST_CHECK_EQUAL(tokens[1].value, "5");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 5);

        BOOST_CHECK_EQUAL(tokens[2].type, token_type::string);
        BOOST_CHECK_EQUAL(tokens[2].value, "6\n");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 9);
    }

    BOOST_AUTO_TEST_CASE(case4) {
        lang::get_tokenizer_config(config);

        tokenize(config, "foo bar baz", tokens);

        BOOST_CHECK_EQUAL(tokens[0].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[0].value, "foo");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK_EQUAL(tokens[1].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[1].value, "bar");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 5);

        BOOST_CHECK_EQUAL(tokens[2].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[2].value, "baz");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 9);
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(can_tokenize_separated_symbols_suite, config_and_tokens_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        lang::get_tokenizer_config(config);

        tokenize(config, "foo 5+6", tokens);

        BOOST_CHECK_EQUAL(tokens[0].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[0].value, "foo");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK_EQUAL(tokens[1].type, token_type::number);
        BOOST_CHECK_EQUAL(tokens[1].value, "5");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 5);

        BOOST_CHECK_EQUAL(tokens[2].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[2].value, "+");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 6);

        BOOST_CHECK_EQUAL(tokens[3].type, token_type::number);
        BOOST_CHECK_EQUAL(tokens[3].value, "6");
        BOOST_CHECK_EQUAL(tokens[3].line, 1);
        BOOST_CHECK_EQUAL(tokens[3].col, 7);
    }

    BOOST_AUTO_TEST_CASE(case2) {
        lang::get_tokenizer_config(config);

        tokenize(config, "foo bar++6", tokens);

        BOOST_CHECK_EQUAL(tokens[0].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[0].value, "foo");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK_EQUAL(tokens[1].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[1].value, "bar");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 5);

        BOOST_CHECK_EQUAL(tokens[2].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[2].value, "++");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 8);

        BOOST_CHECK_EQUAL(tokens[3].type, token_type::number);
        BOOST_CHECK_EQUAL(tokens[3].value, "6");
        BOOST_CHECK_EQUAL(tokens[3].line, 1);
        BOOST_CHECK_EQUAL(tokens[3].col, 10);
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(can_tokenize_parser_rules_tokens_suite, config_and_tokens_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        lang::get_tokenizer_config(config);

        tokenize(config, "prefix '+' ..2 root", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 5u);

        BOOST_CHECK_EQUAL(tokens[0].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[0].value, "prefix");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK_EQUAL(tokens[1].type, token_type::string);
        BOOST_CHECK_EQUAL(tokens[1].value, "+");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 8);

        BOOST_CHECK_EQUAL(tokens[2].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[2].value, "..");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 12);

        BOOST_CHECK_EQUAL(tokens[3].type, token_type::number);
        BOOST_CHECK_EQUAL(tokens[3].value, "2");
        BOOST_CHECK_EQUAL(tokens[3].line, 1);
        BOOST_CHECK_EQUAL(tokens[3].col, 14);

        BOOST_CHECK_EQUAL(tokens[4].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[4].value, "root");
        BOOST_CHECK_EQUAL(tokens[4].line, 1);
        BOOST_CHECK_EQUAL(tokens[4].col, 16);
    }

    BOOST_AUTO_TEST_CASE(case2) {
        lang::get_tokenizer_config(config);

        tokenize(config, "prefix '+' ... before 'foo'", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 5u);

        BOOST_CHECK_EQUAL(tokens[0].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[0].value, "prefix");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK_EQUAL(tokens[1].type, token_type::string);
        BOOST_CHECK_EQUAL(tokens[1].value, "+");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 8);

        BOOST_CHECK_EQUAL(tokens[2].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[2].value, "...");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 12);

        BOOST_CHECK_EQUAL(tokens[3].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[3].value, "before");
        BOOST_CHECK_EQUAL(tokens[3].line, 1);
        BOOST_CHECK_EQUAL(tokens[3].col, 16);

        BOOST_CHECK_EQUAL(tokens[4].type, token_type::string);
        BOOST_CHECK_EQUAL(tokens[4].value, "foo");
        BOOST_CHECK_EQUAL(tokens[4].line, 1);
        BOOST_CHECK_EQUAL(tokens[4].col, 23);
    }

BOOST_AUTO_TEST_SUITE_END()