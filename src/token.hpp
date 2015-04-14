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
        token(bool is_tag, bool eol, bool ws_only, const std::string& raw_val);
        type token_type() const { return type_val; };
        const std::string& content() const { return content_val; };
        const std::string& raw() const { return raw_val; };
        bool is_eol() const { return eol; }
        bool is_ws_only() const { return ws_only; }
        bool is_marked() const { return marked; }
        void mark() { marked = true; };
    private:
        type type_val;
        std::string content_val;
        std::string raw_val;
        bool eol;
        bool ws_only;
        bool marked;
        std::tuple<int,int,type> token_info(const std::string& inside);
    };
}

#endif //_MSTCH_TOKEN_H_
