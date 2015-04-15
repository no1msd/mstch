#include "token.hpp"

using namespace mstch;

token::type token::token_info(char c) {
    switch (c) {
    case '>': return type::partial;
    case '^': return type::inverted_section_open;
    case '/': return type::section_close;
    case '&': return type::unescaped_variable;
    case '#': return type::section_open;
    case '!': return type::comment;
    default: return type::variable;
    }
}

token::token(bool is_tag, bool eol, bool ws_only, const std::string& raw_val):
        eol(eol), ws_only(ws_only), marked(false)
{
    if(is_tag) {
        auto content_begin = raw_val.begin(), content_end = raw_val.end();
        parse_state state = parse_state::prews;
        if(*content_begin == '{' && *(content_end - 1) == '}') {
            state = parse_state::postws;
            type_val = type::unescaped_variable;
            ++content_begin;
            --content_end;
        }
        for(auto it = content_begin; it != content_end;) {
            if(state == parse_state::prews && *it != ' ') {
                state = parse_state::postws;
                if((type_val = token_info(*it++)) == type::variable) {
                    state = parse_state::content;
                    content_begin = it -1;
                }
            } else if(state == parse_state::postws && *it != ' ') {
                content_begin = it++;
                state = parse_state::content;
            } else if(state == parse_state::content && *it == ' ') {
                content_end = it;
            } else {
                ++it;
            }
        }
        content_val = {content_begin, content_end};
    } else {
        type_val = type::text;
        content_val = raw_val;
    }
}
