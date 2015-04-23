#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>

#include "render_context.hpp"
#include "mstch/mstch.hpp"

namespace mstch {
namespace visitor {

class render_section: public boost::static_visitor<std::string> {
 public:
  enum class flag { none, keep_array };
  render_section(
      render_context& ctx,
      const template_type& section,
      flag p_flag = flag::none):
      ctx(ctx), section(section), m_flag(p_flag)
  {
  }

  template<class T>
  inline std::string operator()(const T& t) const {
    return render_context::push(ctx, t).render(section);
  }

private:
  render_context& ctx;
  const template_type& section;
  flag m_flag;
};

template<>
inline std::string render_section::operator()<lambda>(const lambda& fun) const {
  return "";
  /*std::string section_str;
  for(auto& token: section)
    section_str += token.raw();
  return lam(section_str, [this](const std::string& str) {
    return ctx.render(template_type{str});
  });*/
}

template<>
inline std::string render_section::operator()<array>(const array& array) const {
  std::string out;
  if(m_flag == flag::keep_array)
    out += render_context::push(ctx, array).render(section);
  else
    for (auto& item: array)
      out += boost::apply_visitor(
        render_section(ctx, section, flag::keep_array), item);
  return out;
}

}
}
