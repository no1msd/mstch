#include "utils.hpp"

#include <boost/algorithm/string/replace.hpp>

mstch::citer mstch::first_not_ws(mstch::citer begin, mstch::citer end) {
  for (auto it = begin; it != end; ++it)
    if (*it != ' ') return it;
  return end;
}

mstch::citer mstch::first_not_ws(mstch::criter begin, mstch::criter end) {
  for (auto rit = begin; rit != end; ++rit)
    if (*rit != ' ') return --(rit.base());
  return --(end.base());
}

std::string mstch::html_escape(std::string str) {
  boost::replace_all(str, "&", "&amp;");
  boost::replace_all(str, "'", "&#39;");
  boost::replace_all(str, "\"", "&quot;");
  boost::replace_all(str, "<", "&lt;");
  boost::replace_all(str, ">", "&gt;");
  boost::replace_all(str, "/", "&#x2F;");
  return str;
}
