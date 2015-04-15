#include "token.hpp"
#include "utils.hpp"

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

token::token(bool is_tag, bool eol, bool ws_only, const std::string& str):
        m_eol(eol), m_ws_only(ws_only), m_marked(false)
{
    if(is_tag) {
        if(str[0] == '{' && str[str.size() - 1] == '}') {
            m_type = type::unescaped_variable;
            m_content = {first_not_ws(str.begin() + 1, str.end()),
                    first_not_ws(str.rbegin() + 1, str.rend()) + 1};
        } else {
            auto first = first_not_ws(str.begin(), str.end());
            m_type = token_info(*first);
            if(m_type != type::variable)
                first = first_not_ws(first + 1, str.end());
            m_content = {first, first_not_ws(str.rbegin(), str.rend()) + 1};
        }
    } else {
        m_type = type::text;
        m_content = str;
    }
}
