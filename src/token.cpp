#include "token.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>

using namespace mstch;

std::tuple<int,int,token::type> token::token_info(const std::string& inside) {
    switch (inside.at(0)) {
    case '>': return std::make_tuple(1, 0, type::partial);
    case '^': return std::make_tuple(1, 0, type::inverted_section_open);
    case '/': return std::make_tuple(1, 0, type::section_close);
    case '&': return std::make_tuple(1, 0, type::unescaped_variable);
    case '#': return std::make_tuple(1, 0, type::section_open);
    case '!': return std::make_tuple(1, 0, type::comment);
    case '{':
        if (inside.at(inside.size() - 1) == '}')
            return std::make_tuple(1, 1, type::unescaped_variable);
    default: return std::make_tuple(0, 0, type::variable);
    }
}

token::token(bool is_tag_val, const std::string& raw_val):
        raw_val(raw_val), is_tag_val(is_tag_val)
{
    if(is_tag_val) {
        std::string inside{raw_val.substr(2, raw_val.size() - 4)};
        boost::trim(inside);
        if (inside.size() > 0) {
            int lpad, rpad;
            std::tie(lpad, rpad, type_val) = token_info(inside);
            content_val = inside.substr(lpad, inside.size() - lpad - rpad);
            boost::trim(content_val);
        }
    } else {
        type_val = type::text;
        content_val = raw_val;
    }
}

token::type token::token_type() const {
    return type_val;
}

std::string token::content() const {
    return content_val;
}

std::string token::raw() const {
    return raw_val;
}

bool token::is_tag() const {
    return is_tag_val;
}
