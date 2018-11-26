#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <string>
#include "vm_context_methods.hpp"
#include "tokenizer.hpp"
#include "std.hpp"
#include "interpreter.hpp"
#include "lang_tokenizer_cutvm_functions.hpp"

using namespace cuttle;
using namespace cuttle::lang;

struct lang_tokenizer_cutvm_functions_context_init_fixture {
    tokenizer_config_t config;
    std::deque<vm::value_t> arg_stack;
};

BOOST_FIXTURE_TEST_SUITE(lang_tokenizer_cutvm_functions_suite, lang_tokenizer_cutvm_functions_context_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        vm::context_t vm_context;
        vm::populate(vm_context);

        auto tokenizer_config = vm::value_t{{vm::type_id::object},
                                          {&config}};
        vm::add(vm_context, TOKENIZER_CONFIG_VAR_NAME, tokenizer_config);
        register_lang_tokenizer_cutvm_functions(vm_context);

        std::stringstream ss(
                "b s '\n"
                "b s '\n"
                "c 2 2 ->\n"
                "c 1 1 formatted_string");

        while (!ss.eof()) {
            vm::eval(ss, vm_context, arg_stack);
        }

        auto result = (tokenizer_config_t *) vm::get(vm_context, TOKENIZER_CONFIG_VAR_NAME, {vm::type_id::object}).data.object;

        BOOST_CHECK(result->formatted_string["'"] == tokenizer_symbol_set_t{"'"});
    }

    BOOST_AUTO_TEST_CASE(case2) {
        vm::context_t vm_context;
        vm::populate(vm_context);

        auto tokenizer_config = vm::value_t{{vm::type_id::object},
                                            {&config}};
        vm::add(vm_context, TOKENIZER_CONFIG_VAR_NAME, tokenizer_config);
        register_lang_tokenizer_cutvm_functions(vm_context);

        std::stringstream ss(
                "b s \"\n"
                "b s \"\n"
                "c 2 2 ->\n"
                "c 1 1 formatted_string\n"
                "b s \\\\\"\n"
                "b s \"\n"
                "c 2 2 ->\n"
                "c 1 1 formatted_character");

        while (!ss.eof()) {
            vm::eval(ss, vm_context, arg_stack);
        }

        auto result = (tokenizer_config_t *) vm::get(vm_context, TOKENIZER_CONFIG_VAR_NAME, {vm::type_id::object}).data.object;

        BOOST_CHECK(result->formatted_string["\""] == tokenizer_symbol_set_t{"\""});
        BOOST_CHECK_EQUAL(result->formatted_characters["\\\""], "\"");
        BOOST_CHECK_EQUAL(result->formatted_characters_output["\""], "\\\"");
    }

    BOOST_AUTO_TEST_CASE(case3) {
        vm::context_t vm_context;
        vm::populate(vm_context);

        auto tokenizer_config = vm::value_t{{vm::type_id::object},
                                            {&config}};
        vm::add(vm_context, TOKENIZER_CONFIG_VAR_NAME, tokenizer_config);
        register_lang_tokenizer_cutvm_functions(vm_context);

        std::stringstream ss(
                "b b true\n"
                "c 1 1 separate_digit_and_alpha");

        while (!ss.eof()) {
            vm::eval(ss, vm_context, arg_stack);
        }

        auto result = (tokenizer_config_t *) vm::get(vm_context, TOKENIZER_CONFIG_VAR_NAME, {vm::type_id::object}).data.object;

        BOOST_CHECK_EQUAL(result->separate_digit_and_alpha, true);
    }

    BOOST_AUTO_TEST_CASE(case4) {
        vm::context_t vm_context;
        vm::populate(vm_context);

        auto tokenizer_config = vm::value_t{{vm::type_id::object},
                                            {&config}};
        vm::add(vm_context, TOKENIZER_CONFIG_VAR_NAME, tokenizer_config);
        register_lang_tokenizer_cutvm_functions(vm_context);

        std::stringstream ss(
                "b b false\n"
                "c 1 1 separate_digit_and_alpha");

        while (!ss.eof()) {
            vm::eval(ss, vm_context, arg_stack);
        }

        auto result = (tokenizer_config_t *) vm::get(vm_context, TOKENIZER_CONFIG_VAR_NAME, {vm::type_id::object}).data.object;

        BOOST_CHECK_EQUAL(result->separate_digit_and_alpha, false);
    }

    BOOST_AUTO_TEST_CASE(case5) {
        vm::context_t vm_context;
        vm::populate(vm_context);

        auto tokenizer_config = vm::value_t{{vm::type_id::object},
                                            {&config}};
        vm::add(vm_context, TOKENIZER_CONFIG_VAR_NAME, tokenizer_config);
        register_lang_tokenizer_cutvm_functions(vm_context);

        std::stringstream ss(
                "b s -\n"
                "c 1 1 separated_symbol\n"
                "b s +\n"
                "c 1 1 separated_symbol");

        while (!ss.eof()) {
            vm::eval(ss, vm_context, arg_stack);
        }

        auto result = (tokenizer_config_t *) vm::get(vm_context, TOKENIZER_CONFIG_VAR_NAME, {vm::type_id::object}).data.object;

        BOOST_CHECK_EQUAL(result->separated_symbols.size(), 2u);
        BOOST_CHECK_EQUAL(result->separated_symbols.count("+"), 1u);
        BOOST_CHECK_EQUAL(result->separated_symbols.count("-"), 1u);
        BOOST_CHECK_EQUAL(result->separated_symbols.count("not specified"), 0u);
    }

BOOST_AUTO_TEST_SUITE_END()