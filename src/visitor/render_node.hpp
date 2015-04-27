#pragma once

#include <boost/variant/static_visitor.hpp>

#include "mstch/mstch.hpp"
#include "utils.hpp"

namespace mstch {

class render_node: public boost::static_visitor<std::string> {
 public:
  enum class flag { none, escape_html };
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
inline std::string render_node::operator()(const int& value) const {
  return std::to_string(value);
}

template<>
inline std::string render_node::operator()(const bool& value) const {
  return value?"true":"false";
}

template<>
inline std::string render_node::operator()(const lambda& value) const {
  return (m_flag == flag::escape_html)?html_escape(value()):value();
}

template<>
inline std::string render_node::operator()(const std::string& value) const {
    return (m_flag == flag::escape_html)?html_escape(value):value;
}

}
