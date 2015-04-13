#ifndef _MSTCH_TOKEN_H_
#define _MSTCH_TOKEN_H_

#include <string>

namespace mstch {
    class token {
    public:
        enum class type {
            text, variable, section_open, section_close, inverted_section_open,
            unescaped_variable, comment, partial
        };
    private:
        type type_val;
        std::string content_val;
        std::string raw_val;
        std::tuple<int,int,type> token_info(const std::string& inside);
    public:
        token(const std::string& raw_token);
        type token_type() const;
        std::string content() const;
        std::string raw() const;
    };
}

#endif //_MSTCH_TOKEN_H_
