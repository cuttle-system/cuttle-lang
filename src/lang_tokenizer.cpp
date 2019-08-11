#include "lang_tokenizer.hpp"

using namespace cuttle;

void lang::get_tokenizer_config(tokenizer_config_t& config) {
    config.formatted_string = {{"\"", {"\""}}};
    config.normal_string = {{"\'", {"\'"}}};
    config.separated_symbols = {{".", "->", "<-", "++", "+", "*", "/", "-", "=", "(", ")"}};
    config.comments = {{"#", {"\n"}}};
}
