#include "token.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <boost/regex.hpp>

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

token::token(const std::string& raw_token): raw_val(raw_token) {
    boost::regex token_match("\\{{2}[^\\}]*\\}{2}|\\{{3}[^\\}]*\\}{3}");
    if(boost::regex_match(raw_token, token_match)) {
        std::string inside{raw_token.substr(2, raw_token.size() - 4)};
        boost::trim(inside);
        if (inside.size() > 0) {
            int lpad, rpad;
            std::tie(lpad, rpad, type_val) = token_info(inside);
            content_val = inside.substr(lpad, inside.size() - lpad - rpad);
            boost::trim(content_val);
        }
    } else {
        type_val = type::text;
        content_val = raw_token;
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
