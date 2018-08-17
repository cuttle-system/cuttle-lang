#include <iostream>
#include <fstream>
#include <string>
#include "test.hpp"
#include "test_lang_tokenizer.hpp"
#include "tokenizer.hpp"
#include "lang_tokenizer.hpp"

using namespace cuttle;

inline void test_can_tokenize_basic_function_calls() {
    {
        tokenizer_config_t config;
        tokens_t tokens;

        lang::get_tokenizer_config(config);

        tokenize(config, "foo 5 6", tokens);

        AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
        AssertTrue(tokens[0].value == "foo", "element 1 value");
        AssertTrue(tokens[0].line == 1, "element 1 line");
        AssertTrue(tokens[0].col == 1, "element 1 col");

        AssertTrue(tokens[1].type == token_type::number, "element 2 type");
        AssertTrue(tokens[1].value == "5", "element 2 value");
        AssertTrue(tokens[1].line == 1, "element 2 line");
        AssertTrue(tokens[1].col == 5, "element 2 col");

        AssertTrue(tokens[2].type == token_type::number, "element 3 type");
        AssertTrue(tokens[2].value == "6", "element 3 value");
        AssertTrue(tokens[2].line == 1, "element 3 line");
        AssertTrue(tokens[2].col == 7, "element 3 col");
    }
    {
        tokenizer_config_t config;
        tokens_t tokens;

        lang::get_tokenizer_config(config);

        tokenize(config, "foo '5' 6", tokens);

        AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
        AssertTrue(tokens[0].value == "foo", "element 1 value");
        AssertTrue(tokens[0].line == 1, "element 1 line");
        AssertTrue(tokens[0].col == 1, "element 1 col");

        AssertTrue(tokens[1].type == token_type::string, "element 2 type");
        AssertTrue(tokens[1].value == "5", "element 2 value");
        AssertTrue(tokens[1].line == 1, "element 2 line");
        AssertTrue(tokens[1].col == 5, "element 2 col");

        AssertTrue(tokens[2].type == token_type::number, "element 3 type");
        AssertTrue(tokens[2].value == "6", "element 3 value");
        AssertTrue(tokens[2].line == 1, "element 3 line");
        AssertTrue(tokens[2].col == 9, "element 3 col");
    }
    {
        tokenizer_config_t config;
        tokens_t tokens;

        lang::get_tokenizer_config(config);

        tokenize(config, "foo '5' \"6\\n\"", tokens);

        AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
        AssertTrue(tokens[0].value == "foo", "element 1 value");
        AssertTrue(tokens[0].line == 1, "element 1 line");
        AssertTrue(tokens[0].col == 1, "element 1 col");

        AssertTrue(tokens[1].type == token_type::string, "element 2 type");
        AssertTrue(tokens[1].value == "5", "element 2 value");
        AssertTrue(tokens[1].line == 1, "element 2 line");
        AssertTrue(tokens[1].col == 5, "element 2 col");

        AssertTrue(tokens[2].type == token_type::string, "element 3 type");
        AssertTrue(tokens[2].value == "6\n", "element 3 value");
        AssertTrue(tokens[2].line == 1, "element 3 line");
        AssertTrue(tokens[2].col == 9, "element 3 col");
    }
    {
        tokenizer_config_t config;
        tokens_t tokens;

        lang::get_tokenizer_config(config);

        tokenize(config, "foo bar baz", tokens);

        AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
        AssertTrue(tokens[0].value == "foo", "element 1 value");
        AssertTrue(tokens[0].line == 1, "element 1 line");
        AssertTrue(tokens[0].col == 1, "element 1 col");

        AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
        AssertTrue(tokens[1].value == "bar", "element 2 value");
        AssertTrue(tokens[1].line == 1, "element 2 line");
        AssertTrue(tokens[1].col == 5, "element 2 col");

        AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
        AssertTrue(tokens[2].value == "baz", "element 3 value");
        AssertTrue(tokens[2].line == 1, "element 3 line");
        AssertTrue(tokens[2].col == 9, "element 3 col");
    }
}

inline void test_can_tokenize_separated_symbols() {
    {
        tokenizer_config_t config;
        tokens_t tokens;

        lang::get_tokenizer_config(config);

        tokenize(config, "foo 5+6", tokens);

        AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
        AssertTrue(tokens[0].value == "foo", "element 1 value");
        AssertTrue(tokens[0].line == 1, "element 1 line");
        AssertTrue(tokens[0].col == 1, "element 1 col");

        AssertTrue(tokens[1].type == token_type::number, "element 2 type");
        AssertTrue(tokens[1].value == "5", "element 2 value");
        AssertTrue(tokens[1].line == 1, "element 2 line");
        AssertTrue(tokens[1].col == 5, "element 2 col");

        AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
        AssertTrue(tokens[2].value == "+", "element 3 value");
        AssertTrue(tokens[2].line == 1, "element 3 line");
        AssertTrue(tokens[2].col == 6, "element 3 col");

        AssertTrue(tokens[3].type == token_type::number, "element 4 type");
        AssertTrue(tokens[3].value == "6", "element 4 value");
        AssertTrue(tokens[3].line == 1, "element 4 line");
        AssertTrue(tokens[3].col == 7, "element 4 col");
    }
    {
        tokenizer_config_t config;
        tokens_t tokens;

        lang::get_tokenizer_config(config);

        tokenize(config, "foo bar++6", tokens);

        AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
        AssertTrue(tokens[0].value == "foo", "element 1 value");
        AssertTrue(tokens[0].line == 1, "element 1 line");
        AssertTrue(tokens[0].col == 1, "element 1 col");

        AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
        AssertTrue(tokens[1].value == "bar", "element 2 value");
        AssertTrue(tokens[1].line == 1, "element 2 line");
        AssertTrue(tokens[1].col == 5, "element 2 col");

        AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
        AssertTrue(tokens[2].value == "++", "element 3 value");
        AssertTrue(tokens[2].line == 1, "element 3 line");
        AssertTrue(tokens[2].col == 8, "element 3 col");

        AssertTrue(tokens[3].type == token_type::number, "element 4 type");
        AssertTrue(tokens[3].value == "6", "element 4 value");
        AssertTrue(tokens[3].line == 1, "element 4 line");
        AssertTrue(tokens[3].col == 10, "element 4 col");
    }
}

void run_lang_tokenizer_tests() {
    TESTCASE
    test_can_tokenize_basic_function_calls();
    test_can_tokenize_separated_symbols();
}
