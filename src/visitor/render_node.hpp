#pragma once

#include <sstream>
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

  std::string operator()(const int& value) const {
    return std::to_string(value);
  }

  std::string operator()(const double& value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
  }

  std::string operator()(const bool& value) const {
    return value ? "true" : "false";
  }

  std::string operator()(const lambda& value) const {
    return (m_flag == flag::escape_html) ? html_escape(value()) : value();
  }

  std::string operator()(const std::string& value) const {
    return (m_flag == flag::escape_html) ? html_escape(value) : value;
  }

 private:
  flag m_flag;
};

}
