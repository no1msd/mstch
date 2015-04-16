#include "template_type.hpp"

using namespace mstch;

template_type::template_type(const std::string& str) {
    tokenize(str);
    strip_whitespace();
}

void template_type::tokenize(const std::string& t) {
    std::string delim_start{"{{"};
    std::string delim_end{"}}"};
    std::string::const_iterator tok_end, tok_start = t.begin();
    parse_state pstate = parse_state::start;
    unsigned int del_pos = 0;
    bool ws_only = true;
    for (std::string::const_iterator it = t.begin(); it != t.end(); ++it) {
        if (pstate == parse_state::start) {
            if (*it == delim_start[0]) {
                pstate = parse_state::in_del_start;
                tok_end = it;
                del_pos = 1;
            } else if(*it == '\n') {
                tokens.push_back({false, true, ws_only, {tok_start, it + 1}});
                ws_only = true;
                tok_start = it + 1;
            } else if (*it != ' ' && *it != '\t') {
                ws_only = false;
            }
        } else if(pstate == parse_state::in_del_start) {
            if (*it == delim_start[del_pos] && ++del_pos == delim_start.size())
                pstate = parse_state::in_del;
            else
                pstate = parse_state::start;
        } else if(pstate == parse_state::in_del) {
            if (*it == '{')
                pstate = parse_state::in_esccontent;
            else if (*it == delim_end[0] && (del_pos = 1))
                pstate = parse_state::in_del_end;
            else
                pstate = parse_state::in_content;
        } else if(pstate == parse_state::in_esccontent && *it == '}') {
            pstate = parse_state::in_content;
        } else if(pstate == parse_state::in_content && *it == delim_end[0]) {
            pstate = parse_state::in_del_end;
            del_pos = 1;
        } else if(pstate == parse_state::in_del_end) {
            if (*it == delim_end[del_pos] && ++del_pos == delim_end.size()) {
                pstate = parse_state::start;
                tokens.push_back({false, false, ws_only, {tok_start, tok_end}});
                tokens.push_back({true, false, false,
                        {tok_end+delim_start.size(), it-delim_end.size()+1}});
                ws_only = true;
                tok_start = it + 1;
            } else {
                pstate = parse_state::start;
            }
        }
    }
    tokens.push_back({false, false, ws_only, {tok_start, t.end()}});
}

void template_type::strip_whitespace() {
    auto line_begin = tokens.begin();
    bool has_tag = false, non_space = false;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        auto type = (*it).token_type();
        if (type != token::type::text && type != token::type::variable &&
                type != token::type::unescaped_variable)
            has_tag = true;
        else if (!(*it).ws_only())
            non_space = true;
        if ((*it).eol()) {
            if (has_tag && !non_space)
                for (auto line_it = line_begin; line_it != it + 1; ++line_it)
                    if ((*line_it).ws_only()) (*line_it).mark();
            non_space = has_tag = false;
            line_begin = it + 1;
        }
    }
    for (auto it = tokens.begin(); it != tokens.end();)
        ((*it).marked())?(it = tokens.erase(it)):(++it);
}
