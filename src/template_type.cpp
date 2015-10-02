#include "template_type.hpp"

using namespace mstch;

template_type::template_type(const std::string& str) {
  tokenize(str);
  strip_whitespace();
}

void template_type::process_text(citer begin, citer end) {
  if (begin == end)
    return;
  auto start = begin;
  for (auto it = begin; it != end; ++it)
    if (*it == '\n' || it == end - 1) {
      tokens.push_back({{start, it + 1}});
      start = it + 1;
    }
}

void template_type::tokenize(const std::string& tmp) {
  std::string open{"{{"}, close{"}}"};
  citer beg = tmp.begin();
  auto npos = std::string::npos;

  for (unsigned long long cur_pos = 0; cur_pos < tmp.size();) {
    auto open_pos = tmp.find(open, cur_pos);
    auto close_pos = tmp.find(
        close, open_pos == npos ? open_pos : open_pos + 1);

    if (close_pos != npos && open_pos != npos) {
      if (*(beg + open_pos + open.size()) == '{' &&
          *(beg + close_pos + close.size()) == '}')
        ++close_pos;

      process_text(beg + cur_pos, beg + open_pos);
      cur_pos = close_pos + close.size();
      tokens.push_back({{beg + open_pos, beg + close_pos + close.size()},
          open.size(), close.size()});

      if(cur_pos == tmp.size()) {
        tokens.push_back({{""}});
        tokens.back().eol(true);
      }

      if (*(beg + open_pos + open.size()) == '=' &&
          *(beg + close_pos - 1) == '=')
      {
        auto tok_beg = beg + open_pos + open.size() + 1;
        auto tok_end = beg + close_pos - 1;
        auto front_skip = first_not_ws(tok_beg, tok_end);
        auto back_skip = first_not_ws(reverse(tok_end), reverse(tok_beg));
        open = {front_skip, beg + tmp.find(' ', front_skip - beg)};
        close = {beg + tmp.rfind(' ', back_skip - beg) + 1, back_skip + 1};
      }
    } else {
      process_text(beg + cur_pos, tmp.end());
      cur_pos = close_pos;
    }
  }
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
      if (has_tag && !non_space) {
        store_prefixes(line_begin);

        auto c = line_begin;
        for (bool end = false; !end; (*c).ws_only() ? c = tokens.erase(c) : ++c)
          if ((end = (*c).eol()))
            it = c - 1;
      }

      non_space = has_tag = false;
      line_begin = it + 1;
    }
  }
}

void template_type::store_prefixes(std::vector<token>::iterator beg) {
  for (auto cur = beg; !(*cur).eol(); ++cur)
    if ((*cur).token_type() == token::type::partial &&
        cur != beg && (*(cur - 1)).ws_only())
      (*cur).partial_prefix((*(cur - 1)).raw());
}
