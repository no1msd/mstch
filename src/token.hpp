#pragma once

#include <string>

namespace mstch {
    class token {
    public:
        enum class type {
            text, variable, section_open, section_close, inverted_section_open,
            unescaped_variable, comment, partial
        };
        token(const std::string& str, std::size_t skip_left = 0, std::size_t skip_right = 0);
        type token_type() const { return m_type; };
        const std::string& raw() const { return m_raw; };
        const std::string& name() const { return m_name; };
        bool eol() const { return m_eol; }
        bool ws_only() const { return m_ws_only; }
    private:
        type m_type;
        std::string m_name;
        std::string m_raw;
        bool m_eol;
        bool m_ws_only;
        type token_info(char c);
    };
}
