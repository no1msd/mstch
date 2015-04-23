#pragma once

#include <string>
#include <vector>

#include "token.hpp"
#include "utils.hpp"

namespace mstch {

class template_type {
 public:
  template_type() = default;
  template_type(const std::string& str);
  std::vector<token>::const_iterator begin() const { return tokens.begin(); }
  std::vector<token>::const_iterator end() const { return tokens.end(); }
  void operator<<(const token& token) { tokens.push_back(token); }

 private:
  std::vector<token> tokens;
  void strip_whitespace();
  void process_text(citer beg, citer end);
  void tokenize(const std::string& tmplt);
};

}
