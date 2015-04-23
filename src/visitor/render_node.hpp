#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>

#include "mstch/mstch.hpp"
#include "utils.hpp"

namespace mstch {
namespace visitor {

class render_node: public boost::static_visitor<std::string> {
 public:
  enum class flag {
    none, escape_html
  };

  render_node(flag p_flag = flag::none): m_flag(p_flag) {
  }

  template<class T>
  inline std::string operator()(const T& t) const {
    return "";
  }

 private:
  flag m_flag;
};

template<>
inline std::string render_node::operator()<int>(const int& val) const {
  return std::to_string(val);
}

template<> inline
std::string render_node::operator()<bool>(const bool& val) const {
  return val?"true":"false";
}

template<>
inline std::string render_node::operator()<std::string>(
    const std::string& val) const
{
    return (m_flag == flag::escape_html)?html_escape(val):val;
}

}
}
