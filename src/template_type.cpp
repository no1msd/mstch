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

void template_type::tokenize(const std::string& tmplt) {
  std::string o{"{{"}, c{"}}"};
  citer beg = tmplt.begin();
  for (unsigned long pos = 0; pos < tmplt.size();) {
    auto to = tmplt.find(o, pos);
    auto tc = tmplt.find(c, (to == std::string::npos)?to:(to + 1));
    if (tc != std::string::npos && to != std::string::npos) {
      if (*(beg + to + o.size()) == '{' && *(beg + tc + c.size()) == '}')
        ++tc;
      process_text(beg + pos, beg + to);
      pos = tc + c.size();
      tokens.push_back({{beg + to, beg + tc + c.size()}, o.size(), c.size()});
      if (*(beg + to + o.size()) == '=' && *(beg + tc - 1) == '=') {
        o = {beg + to + o.size() + 1, beg + tmplt.find(' ', to)};
        c = {beg + tmplt.find(' ', to) + 1, beg + tc - 1};
      }
    } else {
      process_text(beg + pos, tmplt.end());
      pos = tc;
    }
  }
}

void template_type::strip_whitespace() {
  auto lbegin = tokens.begin();
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
        for (auto c = lbegin; it != c-1; c = (*c).ws_only()?tokens.erase(c):++c)
          it = (*c).eol()?c-1:it;
      non_space = has_tag = false;
      lbegin = it + 1;
    }
  }
}
