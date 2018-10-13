#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <string>
#include "vm_context_methods.hpp"
#include "parser.hpp"
#include "context_methods.hpp"
#include "std.hpp"
#include "interpreter.hpp"
#include "lang_parser_cutvm_functions.hpp"

using namespace cuttle;
using namespace cuttle::lang;

struct lang_parser_cutvm_functions_context_init_fixture {
    context_t context;
    std::deque<vm::value_t> arg_stack;

    void setup() {
        initialize(context);
    }
};

BOOST_FIXTURE_TEST_SUITE(lang_parser_cutvm_functions_suite, lang_parser_cutvm_functions_context_init_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        vm::context_t vm_context;
        vm::populate(vm_context);

        auto parser_config_array = PARSER_CONTEXT_CONFIG_ARRAY_DEFAULT_VALUES;
        auto parser_context = vm::value_t{{vm::type_id::object},
                                          {&context}};
        vm::add(vm_context, PARSER_CONTEXT_ARRAY_VAR_NAME, parser_config_array);
        vm::add(vm_context, PARSER_CONTEXT_VAR_NAME, parser_context);
        register_lang_parser_cutvm_functions(vm_context);

        std::stringstream ss(
                "c 0 0 start_func_id\n"
                "c 1 1 priority_after\n"
                "b s foo\n"
                "c 1 1 name\n"
                "c 0 0 infix\n"
                "c 1 1 type\n"
                "b i 2\n"
                "c 1 1 args_number\n"
                "c 0 0 append_to_context");

        while (!ss.eof()) {
            vm::eval(ss, vm_context, arg_stack);
        }

        auto result_config = *vm::get(vm_context, PARSER_CONTEXT_ARRAY_VAR_NAME,
                                      PARSER_CONTEXT_CONFIG_TYPE).data.array;
        auto result = (context_t *) vm::get(vm_context, PARSER_CONTEXT_VAR_NAME, {vm::type_id::object}).data.object;

        BOOST_CHECK_EQUAL(*result_config[0].data.string, "foo");
        BOOST_CHECK_EQUAL(*result_config[1].data.integral, function_type::infix);
        BOOST_CHECK_EQUAL(*result_config[2].data.integral, 2);
        BOOST_CHECK_EQUAL(*result_config[3].data.integral, FUNCTION_ID_UNKNOWN);

        BOOST_CHECK_EQUAL(result->funcname_to_id["foo"], FUNCTION_ID_START);
        BOOST_CHECK_EQUAL(result->funcs[result->funcname_to_id["foo"]].type, function_type::infix);
        BOOST_CHECK_EQUAL(result->funcs[result->funcname_to_id["foo"]].args_number, 2u);
        BOOST_CHECK_EQUAL(result->funcs_prior.priors[result->funcname_to_id["foo"]].prev, FUNCTION_ID_UNKNOWN);
        BOOST_CHECK_EQUAL(result->funcs_prior.priors[result->funcname_to_id["foo"]].prior, FUNCTION_PRIORITY_START);
        BOOST_CHECK_EQUAL(result->funcs_prior.priors[result->funcname_to_id["foo"]].next, FUNCTION_ID_LAST);
    }

    BOOST_AUTO_TEST_CASE(case2) {
            vm::context_t vm_context;
            vm::populate(vm_context);

            auto parser_config_array = PARSER_CONTEXT_CONFIG_ARRAY_DEFAULT_VALUES;
            auto parser_context = vm::value_t{{vm::type_id::object},
                                              {&context}};
            vm::add(vm_context, PARSER_CONTEXT_ARRAY_VAR_NAME, parser_config_array);
            vm::add(vm_context, PARSER_CONTEXT_VAR_NAME, parser_context);
            register_lang_parser_cutvm_functions(vm_context);

            std::stringstream ss(
                    "c 0 0 start_func_id\n"
                    "c 1 1 priority_after\n"
                    "b s foo\n"
                    "c 1 1 name\n"
                    "c 0 0 infix\n"
                    "c 1 1 type\n"
                    "b i 2\n"
                    "c 1 1 args_number\n"
                    "c 0 0 append_to_context\n"
                    "b s foo\n"
                    "c 1 1 func_id\n"
                    "c 1 1 priority_after\n"
                    "b s bar\n"
                    "c 1 1 name\n"
                    "c 0 0 prefix\n"
                    "c 1 1 type\n"
                    "b i 2\n"
                    "c 1 1 args_number\n"
                    "c 0 0 append_to_context");

            while (!ss.eof()) {
                    vm::eval(ss, vm_context, arg_stack);
            }

            auto result_config = *vm::get(vm_context, PARSER_CONTEXT_ARRAY_VAR_NAME,
                                          PARSER_CONTEXT_CONFIG_TYPE).data.array;
            auto result = (context_t *) vm::get(vm_context, PARSER_CONTEXT_VAR_NAME, {vm::type_id::object}).data.object;

            BOOST_CHECK_EQUAL(*result_config[0].data.string, "bar");
            BOOST_CHECK_EQUAL(*result_config[1].data.integral, function_type::prefix);
            BOOST_CHECK_EQUAL(*result_config[2].data.integral, 2);
            BOOST_CHECK_EQUAL(*result_config[3].data.integral, FUNCTION_ID_START);

            BOOST_CHECK_EQUAL(result->funcname_to_id["foo"], FUNCTION_ID_START);
            BOOST_CHECK_EQUAL(result->funcs[result->funcname_to_id["foo"]].type, function_type::infix);
            BOOST_CHECK_EQUAL(result->funcs[result->funcname_to_id["foo"]].args_number, 2u);
            BOOST_CHECK_EQUAL(result->funcs_prior.priors[result->funcname_to_id["foo"]].prev, FUNCTION_ID_UNKNOWN);
            BOOST_CHECK_EQUAL(result->funcs_prior.priors[result->funcname_to_id["foo"]].prior, FUNCTION_PRIORITY_START);
            BOOST_CHECK_EQUAL(result->funcs_prior.priors[result->funcname_to_id["foo"]].next, FUNCTION_ID_START + 1);

            BOOST_CHECK_EQUAL(result->funcname_to_id["bar"], FUNCTION_ID_START + 1);
            BOOST_CHECK_EQUAL(result->funcs[result->funcname_to_id["bar"]].type, function_type::prefix);
            BOOST_CHECK_EQUAL(result->funcs[result->funcname_to_id["bar"]].args_number, 2u);
            BOOST_CHECK_EQUAL(result->funcs_prior.priors[result->funcname_to_id["bar"]].prev, FUNCTION_ID_START);
            BOOST_CHECK_EQUAL(result->funcs_prior.priors[result->funcname_to_id["bar"]].prior, FUNCTION_PRIORITY_START + 1);
            BOOST_CHECK_EQUAL(result->funcs_prior.priors[result->funcname_to_id["bar"]].next, FUNCTION_ID_LAST);
    }

BOOST_AUTO_TEST_SUITE_END()