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
        token(bool is_tag, bool eol, bool ws_only, const std::string& str);
        type token_type() const { return m_type; };
        const std::string& content() const { return m_content; };
        bool eol() const { return m_eol; }
        bool ws_only() const { return m_ws_only; }
        bool marked() const { return m_marked; }
        void mark() { m_marked = true; };
    private:
        type m_type;
        std::string m_content;
        bool m_eol;
        bool m_ws_only;
        bool m_marked;
        type token_info(char c);
    };
}

#endif //_MSTCH_TOKEN_H_
