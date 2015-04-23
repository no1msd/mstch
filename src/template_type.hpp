#pragma once

#include <string>
#include <vector>

#include "token.hpp"

namespace mstch {

class template_type {
 public:
  template_type() = default;
  template_type(const std::string& str);
  std::vector<token>::const_iterator begin() const { return tokens.begin(); }
  std::vector<token>::const_iterator end() const { return tokens.end(); }
  void operator<<(const token& token) { tokens.push_back(token); }

 private:
  enum class parse_state {
    start, in_del_start, in_del, in_content, in_esccontent, in_del_end
  };
  void tokenize(const std::string& str);
  void strip_whitespace();
  std::vector<token> tokens;
};

}
