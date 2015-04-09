#ifndef _MSTCH_TOKEN_H_
#define _MSTCH_TOKEN_H_

#include <string>

namespace mstch {
    enum class token_type {
        text, variable, section_open, section_close, inverted_section_open, unescaped_variable, comment, partial
    };

    class token {
    private:
        token_type type_val;
        std::string content_val;
        std::string raw_val;

    public:
        token(const std::string& raw_token);
        token_type type() const;
        std::string content() const;
        std::string raw() const;
    };
}

#endif //_MSTCH_TOKEN_H_
