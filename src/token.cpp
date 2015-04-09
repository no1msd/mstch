#include "token.h"

#include "utils.h"
#include <regex>

using namespace mstch;

token::token(const std::string& raw_token): raw_val(raw_token) {
    if(std::regex_match(raw_token, std::regex("\\{{2}[^\\}]*\\}{2}|\\{{3}[^\\}]*\\}{3}"))) {
        std::string inside = raw_token.substr(2, raw_token.size() - 4);
        inside = trim(inside);
        if (inside.size() > 0 && inside.at(0) == '#') {
            type_val = token_type::section_open;
            content_val = inside.substr(1);
        } else if (inside.size() > 0 && inside.at(0) == '>') {
            type_val = token_type::partial;
            content_val = inside.substr(1);
        } else if (inside.size() > 0 && inside.at(0) == '^') {
            type_val = token_type::inverted_section_open;
            content_val = inside.substr(1);
        } else if (inside.size() > 0 && inside.at(0) == '/') {
            type_val = token_type::section_close;
            content_val = inside.substr(1);
        } else if (inside.size() > 0 && inside.at(0) == '&') {
            type_val = token_type::unescaped_variable;
            content_val = inside.substr(1);
        } else if (inside.size() > 0 && inside.at(0) == '{' && inside.at(inside.size() - 1) == '}') {
            type_val = token_type::unescaped_variable;
            content_val = inside.substr(1, inside.size() - 2);
        } else if (inside.size() > 0 && inside.at(0) == '!') {
            type_val = token_type::comment;
            content_val = inside.substr(1);
        } else {
            type_val = token_type::variable;
            content_val = inside;
        }
        content_val = trim(content_val);
    } else {
        type_val = token_type::text;
        content_val = raw_token;
    }
}

token_type token::type() const {
    return type_val;
}

std::string token::content() const {
    return content_val;
}

std::string token::raw() const {
    return raw_val;
}
